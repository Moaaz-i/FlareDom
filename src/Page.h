#pragma once
#include <Arduino.h>
#include <vector>
#include "Element.h"

class Page {
private:
    String title;
    std::vector<Element> bodyElements;
    String globalCSS;

public:
    Page(const String &t) : title(t) {}

    void add(const Element &el) {
        bodyElements.push_back(el);
    }

    void setGlobalCSS(const String &css) {
        globalCSS = css;
    }

    String render() {
        String body = "";
        for (auto &el : bodyElements) {
            body += el.render();
            body += "\n";
        }

        String s = "<!DOCTYPE html><html lang=\"ar\" dir=\"rtl\"><head>";
        s += "<meta charset=\"UTF-8\">";
        s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
        s += "<title>" + title + "</title>";

        if (globalCSS.length()) {
            s += "<style>" + globalCSS + "</style>";
        }

        s += "</head><body>";
        s += body;
        s += "</body></html>";
        return s;
    }
};
