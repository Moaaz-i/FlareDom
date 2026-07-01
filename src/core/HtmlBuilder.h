#pragma once
#include <Arduino.h>
#include <vector>
#include "../Element.h"
#include "../Page.h"

class HtmlBuilder {
public:
    static String minify(const String &html) {
        String out = "";
        out.reserve(html.length());

        bool skipSpace = false;
        for (size_t i = 0; i < html.length(); i++) {
            char c = html[i];

            if (c == '\n' || c == '\t') continue;
            if (c == ' ') {
                if (skipSpace) continue;
                skipSpace = true;
            } else {
                skipSpace = false;
            }

            out += c;
        }
        return out;
    }

    static void minifyTo(const String &html, String &out) {
        out.reserve(out.length() + html.length());
        bool skipSpace = false;
        for (size_t i = 0; i < html.length(); i++) {
            char c = html[i];
            if (c == '\n' || c == '\t') continue;
            if (c == ' ') {
                if (skipSpace) continue;
                skipSpace = true;
            } else {
                skipSpace = false;
            }
            out += c;
        }
    }

    static String build(Page &page, bool compress = true) {
        String html = page.render();
        return compress ? minify(html) : html;
    }

    static void buildTo(Page &page, String &out, bool compress = true) {
        if (compress) {
            String temp;
            temp.reserve(4096);
            page.renderTo(temp);
            minifyTo(temp, out);
        } else {
            page.renderTo(out);
        }
    }
};
