#pragma once
#include <Arduino.h>

struct Style {
  String raw;

  Style &add(const String &rule) {
    if (raw.length())
      raw += ";";
    raw += rule;
    return *this;
  }

  Style &add(const __FlashStringHelper *rule) {
    if (raw.length())
      raw += ";";
    raw += rule;
    return *this;
  }

  String toString() const { return raw; }

  // ─── Feature 6: CSS Shortcut Methods ───

  Style &bg(const String &val) { return add("background:" + val); }
  Style &color(const String &val) { return add("color:" + val); }
  Style &padding(const String &val) { return add("padding:" + val); }
  Style &margin(const String &val) { return add("margin:" + val); }
  Style &radius(const String &val) { return add("border-radius:" + val); }
  Style &fontSize(const String &val) { return add("font-size:" + val); }
  Style &border(const String &val) { return add("border:" + val); }
  Style &width(const String &val) { return add("width:" + val); }
  Style &height(const String &val) { return add("height:" + val); }
  Style &display(const String &val) { return add("display:" + val); }
  Style &textAlign(const String &val) { return add("text-align:" + val); }
  Style &fontWeight(const String &val) { return add("font-weight:" + val); }
  Style &opacity(const String &val) { return add("opacity:" + val); }
  Style &cursor(const String &val) { return add("cursor:" + val); }
  Style &shadow(const String &val) { return add("box-shadow:" + val); }
  Style &transition(const String &val) { return add("transition:" + val); }
  Style &maxWidth(const String &val) { return add("max-width:" + val); }
  Style &minHeight(const String &val) { return add("min-height:" + val); }
  Style &overflow(const String &val) { return add("overflow:" + val); }
  Style &position(const String &val) { return add("position:" + val); }
  Style &gap(const String &val) { return add("gap:" + val); }
  Style &flexDirection(const String &val) {
    return add("flex-direction:" + val);
  }
  Style &justifyContent(const String &val) {
    return add("justify-content:" + val);
  }
  Style &alignItems(const String &val) { return add("align-items:" + val); }
  Style &gridTemplateColumns(const String &val) {
    return add("grid-template-columns:" + val);
  }
};
