#pragma once
#include <Arduino.h>
#include <vector>
#include "Element.h"
#include "Animation.h"

// Feature 20: Enhanced Page with meta, external CSS, favicon, language, animations
class Page {
private:
    String title;
    std::vector<Element> bodyElements;
    String globalCSS;
    String lang = "ar";
    String dir = "rtl";
    String faviconUrl;
    std::vector<String> metaTags;
    std::vector<String> externalCSS;
    std::vector<Animation> animations;

public:
    Page(const String &t) : title(t) {}

    void add(const Element &el) {
        bodyElements.push_back(el);
    }

    void setGlobalCSS(const String &css) {
        globalCSS = css;
    }

    void appendCSS(const String &css) {
        if (globalCSS.length()) globalCSS += " ";
        globalCSS += css;
    }

    void setLang(const String &l) {
        lang = l;
        dir = (l == "ar" || l == "he" || l == "fa" || l == "ur") ? "rtl" : "ltr";
    }

    void setDir(const String &d) {
        dir = d;
    }

    void addMeta(const String &name, const String &content) {
        metaTags.push_back("<meta name=\"" + name + "\" content=\"" + content + "\">");
    }

    void addExternalCSS(const String &url) {
        externalCSS.push_back("<link rel=\"stylesheet\" href=\"" + url + "\">");
    }

    void addFavicon(const String &url) {
        faviconUrl = url;
    }

    void addAnimation(const Animation &anim) {
        animations.push_back(anim);
    }

    String render() {
        String body = "";
        for (auto &el : bodyElements) {
            body += el.render();
            body += "\n";
        }

        String s = "<!DOCTYPE html><html lang=\"" + lang + "\" dir=\"" + dir + "\"><head>";
        s += "<meta charset=\"UTF-8\">";
        s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
        s += "<title>" + title + "</title>";

        // Meta tags
        for (const auto &meta : metaTags) {
            s += meta;
        }

        // Favicon
        if (faviconUrl.length()) {
            s += "<link rel=\"icon\" href=\"" + faviconUrl + "\">";
        }

        // External CSS
        for (const auto &css : externalCSS) {
            s += css;
        }

        // Global CSS + Animations
        String allCSS = globalCSS;
        for (const auto &anim : animations) {
            allCSS += " " + anim.toCSS();
        }
        if (allCSS.length()) {
            s += "<style>" + allCSS + "</style>";
        }

        s += "</head><body>";
        s += body;
        s += "</body></html>";
        return s;
    }
};
