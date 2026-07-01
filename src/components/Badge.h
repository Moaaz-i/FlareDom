#pragma once
#include "../Component.h"

// Feature 13: Status Badge
class Badge : public Component {
private:
  String label;
  String variant;

public:
  Badge(const String &l, const String &v = "info") : label(l), variant(v) {}

  Element render() override {
    return Element::create("span")
        .addClass("flare-badge")
        .addClass("flare-badge-" + variant)
        .text(label);
  }

  static String css() {
    return ".flare-badge{"
           "display:inline-block;"
           "padding:4px 10px;"
           "border-radius:99px;"
           "font-size:12px;"
           "font-weight:600;"
           "letter-spacing:0.3px;"
           "}"
           ".flare-badge-info{background:rgba(59,130,246,0.15);color:#60a5fa;}"
           ".flare-badge-success{background:rgba(34,197,94,0.15);color:#4ade80;"
           "}"
           ".flare-badge-warning{background:rgba(245,158,11,0.15);color:#"
           "fbbf24;}"
           ".flare-badge-danger{background:rgba(239,68,68,0.15);color:#f87171;}"
           ".flare-badge-neutral{background:rgba(255,255,255,0.08);color:#"
           "94a3b8;}";
  }
};
