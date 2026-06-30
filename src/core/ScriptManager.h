#pragma once
#include <Arduino.h>
#include <vector>
#include "../Element.h"

class ScriptManager {
private:
    std::vector<String> scripts;

public:
    void add(const String &code) {
        scripts.push_back(code);
    }

    Element render() {
        Element script = Element::create("script");

        String all = "";
        for (const auto &s : scripts) {
            all += s;
            all += "\n";
        }

        script.text(all);
        return script;
    }

    void addFunction(const String &name, const String &body) {
        String fn = "function " + name + "(){" + body + "}";
        add(fn);
    }

    void addEvent(const String &selector, const String &event, const String &handler) {
        String code =
            "document.querySelector('" + selector + "').addEventListener('" + event + "', function(){"
            + handler +
            "});";
        add(code);
    }
};
