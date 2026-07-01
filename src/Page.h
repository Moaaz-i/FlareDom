#pragma once
#include "Animation.h"
#include "Element.h"
#include <Arduino.h>
#include <vector>

class Page {
private:
  String title;
  std::vector<Element> bodyElements;
  String globalCSS;
  const __FlashStringHelper *flashGlobalCSS = nullptr;
  String lang = "ar";
  String dir = "rtl";
  String faviconUrl;
  std::vector<String> metaTags;
  std::vector<String> externalCSS;
  std::vector<String> externalScripts;
  std::vector<Animation> animations;

  // SEO, Tailwind, Fonts, Refresh, Scrollbar
  bool tailwindEnabled = false;
  std::vector<String> googleFonts;
  int refreshInterval = 0;
  bool customScrollbar = false;
  String scrollbarColor;
  String scrollbarTrack;

public:
  Page(const String &t) : title(t) {}

  void add(const Element &el) { bodyElements.push_back(el); }

  void setGlobalCSS(const String &css) {
    globalCSS = css;
    flashGlobalCSS = nullptr;
  }

  void setGlobalCSS(const __FlashStringHelper *css) {
    flashGlobalCSS = css;
    globalCSS = "";
  }

  void appendCSS(const String &css) {
    if (globalCSS.length())
      globalCSS += " ";
    globalCSS += css;
  }

  void setLang(const String &l) {
    lang = l;
    dir = (l == "ar" || l == "he" || l == "fa" || l == "ur") ? "rtl" : "ltr";
  }

  void setDir(const String &d) { dir = d; }

  void addMeta(const String &name, const String &content) {
    metaTags.push_back("<meta name=\"" + name + "\" content=\"" + content +
                       "\">");
  }

  void setDescription(const String &desc) { addMeta("description", desc); }

  void setKeywords(const String &keys) { addMeta("keywords", keys); }

  void addExternalCSS(const String &url) {
    externalCSS.push_back("<link rel=\"stylesheet\" href=\"" + url + "\">");
  }

  void addExternalScript(const String &url, bool async = true) {
    externalScripts.push_back("<script src=\"" + url + "\"" +
                              (async ? " async" : "") + "></script>");
  }

  void addFavicon(const String &url) { faviconUrl = url; }

  void addAnimation(const Animation &anim) { animations.push_back(anim); }

  void enableTailwind() { tailwindEnabled = true; }

  void addGoogleFont(const String &font) { googleFonts.push_back(font); }

  void setAutoRefresh(int seconds) { refreshInterval = seconds; }

  void enableCustomScrollbar(const String &thumbColor = "#3b82f6",
                             const String &trackColor = "#0f172a") {
    customScrollbar = true;
    scrollbarColor = thumbColor;
    scrollbarTrack = trackColor;
  }

  void renderTo(String &s) {
    s +=
        "<!DOCTYPE html><html lang=\"" + lang + "\" dir=\"" + dir + "\"><head>";
    s += "<meta charset=\"UTF-8\">";
    s += "<meta name=\"viewport\" content=\"width=device-width, "
         "initial-scale=1.0\">";
    s += "<title>" + title + "</title>";

    if (refreshInterval > 0) {
      s += "<meta http-equiv=\"refresh\" content=\"" + String(refreshInterval) +
           "\">";
    }

    // Meta tags
    for (const auto &meta : metaTags) {
      s += meta;
    }

    // Favicon
    if (faviconUrl.length()) {
      s += "<link rel=\"icon\" href=\"" + faviconUrl + "\">";
    }

    // Google Fonts
    if (googleFonts.size() > 0) {
      s += "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">";
      s += "<link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" "
           "crossorigin>";
      for (const auto &font : googleFonts) {
        String processedFont = font;
        processedFont.replace(" ", "+");
        s += "<link href=\"https://fonts.googleapis.com/css2?family=" +
             processedFont + "&display=swap\" rel=\"stylesheet\">";
      }
    }

    // Tailwind CSS
    if (tailwindEnabled) {
      s += "<script src=\"https://cdn.tailwindcss.com\"></script>";
    }

    // External CSS
    for (const auto &css : externalCSS) {
      s += css;
    }

    // External Scripts
    for (const auto &scr : externalScripts) {
      s += scr;
    }

    // Global CSS + Custom Scrollbar + Animations
    String allCSS = "";
    if (flashGlobalCSS) {
      allCSS += String(flashGlobalCSS);
    } else {
      allCSS += globalCSS;
    }
    for (const auto &anim : animations) {
      allCSS += " " + anim.toCSS();
    }
    if (customScrollbar) {
      allCSS += " ::-webkit-scrollbar{width:8px;height:8px;}"
                " ::-webkit-scrollbar-track{background:" +
                scrollbarTrack +
                ";}"
                " ::-webkit-scrollbar-thumb{background:" +
                scrollbarColor + ";border-radius:4px;}";
    }
    if (allCSS.length()) {
      s += "<style>" + allCSS + "</style>";
    }

    s += "</head><body>";
    for (auto &el : bodyElements) {
      el.renderTo(s);
      s += "\n";
    }
    s += "</body></html>";
  }

  String render() {
    String s = "";
    s.reserve(4096); // pre-allocate for the entire page
    renderTo(s);
    return s;
  }
};
