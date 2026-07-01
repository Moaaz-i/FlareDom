#pragma once
#include "../Component.h"

// Feature 10: Form Input field
class Input : public Component {
private:
  String type;
  String name;
  String placeholder;
  String label;
  String value;
  bool isRequired = false;

public:
  Input(const String &t, const String &n, const String &ph = "")
      : type(t), name(n), placeholder(ph) {}

  Input &setLabel(const String &l) {
    label = l;
    return *this;
  }

  Input &setValue(const String &v) {
    value = v;
    return *this;
  }

  Input &required() {
    isRequired = true;
    return *this;
  }

  Element render() override {
    Element wrapper = Element::create("div").addClass("flare-input-group");

    if (label.length()) {
      wrapper.addChild(Element::create("label")
                           .addClass("flare-label")
                           .attr("for", name)
                           .text(label));
    }

    Element input = Element::create("input")
                        .addClass("flare-input")
                        .attr("type", type)
                        .attr("name", name)
                        .attr("id", name);

    if (placeholder.length())
      input.attr("placeholder", placeholder);
    if (value.length())
      input.attr("value", value);
    if (isRequired)
      input.attr("required", "required");

    wrapper.addChild(input);
    return wrapper;
  }

  static String css() {
    return ".flare-input-group{"
           "margin-bottom:16px;"
           "text-align:left;"
           "}"
           ".flare-label{"
           "display:block;"
           "margin-bottom:6px;"
           "font-size:13px;"
           "font-weight:500;"
           "color:#94a3b8;"
           "}"
           ".flare-input{"
           "width:100%;"
           "padding:10px 14px;"
           "background:rgba(255,255,255,0.06);"
           "border:1px solid rgba(255,255,255,0.12);"
           "border-radius:8px;"
           "color:#fff;"
           "font-size:14px;"
           "font-family:inherit;"
           "outline:none;"
           "transition:border-color 0.2s ease;"
           "box-sizing:border-box;"
           "}"
           ".flare-input:focus{"
           "border-color:#3b82f6;"
           "box-shadow:0 0 0 3px rgba(59,130,246,0.15);"
           "}"
           ".flare-input::placeholder{color:rgba(255,255,255,0.3);}";
  }
};
