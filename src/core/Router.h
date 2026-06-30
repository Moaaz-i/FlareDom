#pragma once
#include <Arduino.h>
#include <functional>
#include <map>

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

public:
  Router(AsyncWebServer *srv) : server(srv) {}

  void addRoute(const String &path, std::function<Page()> callback) {
    routes[path] = callback;

    server->on(path.c_str(), HTTP_GET,
               [this, path](AsyncWebServerRequest *request) {
                 Page p = routes[path]();
                 String html = HtmlBuilder::build(p, true);
                 request->send(200, "text/html", html);
               });
  }

  void setNotFound(std::function<Page()> callback) {
    server->onNotFound([this, callback](AsyncWebServerRequest *request) {
      Page p = callback();
      String html = HtmlBuilder::build(p, true);
      request->send(404, "text/html", html);
    });
  }
};
