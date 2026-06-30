#pragma once
#include <Arduino.h>
#include <map>
#include <functional>
#include <ESP8266WebServer.h>
#include "../Page.h"
#include "HtmlBuilder.h"

class Router {
private:
    ESP8266WebServer *server;
    std::map<String, std::function<Page()>> routes;

public:
    Router(ESP8266WebServer *srv) : server(srv) {}

    void addRoute(const String &path, std::function<Page()> callback) {
        routes[path] = callback;

        server->on(path, [this, path]() {
            Page p = routes[path]();
            String html = HtmlBuilder::build(p, true);
            server->send(200, "text/html", html);
        });
    }

    void setNotFound(std::function<Page()> callback) {
        server->onNotFound([this, callback]() {
            Page p = callback();
            String html = HtmlBuilder::build(p, true);
            server->send(404, "text/html", html);
        });
    }
};
