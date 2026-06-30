#pragma once
#include <Arduino.h>
#include "../Element.h"

// Feature: Real-time update component via WebSockets (v1.2.0)
class WebSocketValue {
private:
    String wsUrl; // e.g. "ws://192.168.1.50/ws"
    String elementId;
    String displayPrefix;
    String displaySuffix;

public:
    WebSocketValue(const String &url, const String &elId)
        : wsUrl(url), elementId(elId) {}

    WebSocketValue &prefix(const String &p) { displayPrefix = p; return *this; }
    WebSocketValue &suffix(const String &s) { displaySuffix = s; return *this; }

    Element render() {
        return Element::create("span")
            .attr("id", elementId)
            .addClass("flare-live-value")
            .text("--");
    }

    Element script() {
        String code = 
            "(function() {"
            "  var ws;"
            "  function connect() {"
            "    ws = new WebSocket('" + wsUrl + "');"
            "    ws.onmessage = function(event) {"
            "      document.getElementById('" + elementId + "').innerText = "
            "        '" + displayPrefix + "' + event.data + '" + displaySuffix + "';"
            "    };"
            "    ws.onclose = function() {"
            "      setTimeout(connect, 2000);"
            "    };"
            "  }"
            "  connect();"
            "})();";
        return Element::create("script").text(code);
    }
};
