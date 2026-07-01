#pragma once
#include <Arduino.h>
#include <map>
#include <vector>
#include <functional>

#if defined(ESP8266)
  #include <ESPAsyncWebServer.h>
#elif defined(ESP32)
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif

#include "../Page.h"
#include "HtmlBuilder.h"

class Router {
private:
    AsyncWebServer *server;
    std::map<String, std::function<Page()>> routes;
    std::vector<String> protectedRoutes;
    std::map<String, String> customHeaders;
    std::map<String, std::function<void(const String&)>> wsCommandCallbacks;

    bool authRequired = false;
    String authUsername;
    String authPassword;
    std::function<void(AsyncWebServerRequest*)> customNotFoundHandler;

    bool isRouteProtected(const String &path) const {
        if (!authRequired) return false;
        for (const auto &p : protectedRoutes) {
            if (p == path) return true;
        }
        return false;
    }

    void applyHeaders(AsyncWebServerResponse *response) {
        for (const auto &kv : customHeaders) {
            response->addHeader(kv.first, kv.second);
        }
    }

public:
    static Router* instance;

    Router(AsyncWebServer *srv) : server(srv) {
        instance = this;

        // Register default catch-all not-found handler to resolve dynamic bindings & auth
        server->onNotFound([this](AsyncWebServerRequest *request) {
            String path = request->url();

            // 1. Check for dynamic bound values
            auto &dynRoutes = getGlobalDynamicRoutes();
            if (dynRoutes.count(path)) {
                if (isRouteProtected(path)) {
                    if (!request->authenticate(authUsername.c_str(), authPassword.c_str())) {
                        return request->requestAuthentication();
                    }
                }
                AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", dynRoutes[path]());
                applyHeaders(response);
                request->send(response);
                return;
            }

            // 2. Custom or Default not found page
            if (customNotFoundHandler) {
                // Wrap in authentication if needed (though usually 404 is public)
                customNotFoundHandler(request);
            } else {
                request->send(404, "text/plain", "Not Found");
            }
        });
    }

    void setCredentials(const String &username, const String &password) {
        authUsername = username;
        authPassword = password;
        authRequired = true;
    }

    void protectRoute(const String &path) {
        protectedRoutes.push_back(path);
    }

    void addHeader(const String &name, const String &value) {
        customHeaders[name] = value;
    }

    void addRedirect(const String &from, const String &to) {
        server->on(from.c_str(), HTTP_GET, [to](AsyncWebServerRequest *request) {
            request->redirect(to);
        });
    }

    #if defined(ESP8266) || defined(ESP32)
    void serveStatic(const String &uri, fs::FS &fs, const String &path, const String &cacheControl = String()) {
        server->serveStatic(uri.c_str(), fs, path.c_str(), cacheControl.c_str());
    }
    #endif

    void addRoute(const String &path, std::function<Page()> callback, bool requireAuth = false) {
        routes[path] = callback;
        if (requireAuth) {
            protectRoute(path);
        }

        server->on(path.c_str(), HTTP_GET, [this, path](AsyncWebServerRequest *request) {
            if (isRouteProtected(path)) {
                if (!request->authenticate(authUsername.c_str(), authPassword.c_str())) {
                    return request->requestAuthentication();
                }
            }

            Page p = routes[path]();
            String html;
            html.reserve(4096);
            HtmlBuilder::buildTo(p, html, true);
            
            AsyncWebServerResponse *response = request->beginResponse(200, "text/html", html);
            applyHeaders(response);
            request->send(response);
        });
    }

    void setNotFound(std::function<Page()> callback) {
        customNotFoundHandler = [this, callback](AsyncWebServerRequest *request) {
            Page p = callback();
            String html;
            html.reserve(2048);
            HtmlBuilder::buildTo(p, html, true);
            
            AsyncWebServerResponse *response = request->beginResponse(404, "text/html", html);
            applyHeaders(response);
            request->send(response);
        };
    }

    // WebSocket C++ command binding
    void onWsCommand(const String &command, std::function<void(const String&)> cb) {
        wsCommandCallbacks[command] = cb;
    }

    void handleWsMessage(const String &msg) {
        int idx = msg.indexOf(':');
        if (idx != -1) {
            String cmd = msg.substring(0, idx);
            String payload = msg.substring(idx + 1);
            if (wsCommandCallbacks.count(cmd)) {
                wsCommandCallbacks[cmd](payload);
            }
        } else {
            if (wsCommandCallbacks.count(msg)) {
                wsCommandCallbacks[msg]("");
            }
        }
    }
};

inline Router* Router::instance = nullptr;
