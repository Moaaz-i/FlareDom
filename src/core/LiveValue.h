#pragma once
#include <Arduino.h>
#include "../Element.h"
#include "../IDGen.h"

// Feature 19: Auto-updating value via AJAX fetch
class LiveValue {
private:
    String endpoint;
    String elementId;
    unsigned long intervalMs;
    String displayPrefix;
    String displaySuffix;

public:
    LiveValue(const String &ep, const String &elId, unsigned long ms = 1000)
        : endpoint(ep), elementId(elId), intervalMs(ms) {}

    LiveValue &prefix(const String &p) { displayPrefix = p; return *this; }
    LiveValue &suffix(const String &s) { displaySuffix = s; return *this; }

    // The display element (where the value appears)
    Element render() {
        return Element::create("span")
            .attr("id", elementId)
            .addClass("flare-live-value")
            .text("--");
    }

    // The <script> element for auto-updating
    Element script() {
        String code = "function _lv_" + elementId + "(){"
            "fetch('" + endpoint + "')"
            ".then(function(r){return r.text();})"
            ".then(function(v){"
            "document.getElementById('" + elementId + "').innerText="
            "'" + displayPrefix + "'+v+'" + displaySuffix + "';"
            "});"
            "}"
            "_lv_" + elementId + "();"
            "setInterval(_lv_" + elementId + "," + String(intervalMs) + ");";

        return Element::create("script").text(code);
    }

    static String css() {
        return
            ".flare-live-value{"
                "font-variant-numeric:tabular-nums;"
                "font-weight:600;"
                "transition:color 0.3s ease;"
            "}";
    }
};
