#pragma once
#include "../Element.h"
#include "../Page.h"
#include <Arduino.h>
#include <vector>

class HtmlBuilder {
public:
  static String minify(const String &html) {
    String out = "";
    out.reserve(html.length());

    bool skipSpace = false;
    for (size_t i = 0; i < html.length(); i++) {
      char c = html[i];

      if (c == '\n' || c == '\t')
        continue;
      if (c == ' ') {
        if (skipSpace)
          continue;
        skipSpace = true;
      } else {
        skipSpace = false;
      }

      out += c;
    }
    return out;
  }

  static String build(Page &page, bool compress = true) {
    String html = page.render();
    return compress ? minify(html) : html;
  }
};
