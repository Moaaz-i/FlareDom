#pragma once
#include "../Component.h"

// Feature 14: Alert/Notification Box
class AlertBox : public Component {
private:
  String type;
  String title;
  String message;
  bool dismissible = false;

public:
  AlertBox(const String &t, const String &ttl, const String &msg = "")
      : type(t), title(ttl), message(msg) {}

  AlertBox &setDismissible(bool d) {
    dismissible = d;
    return *this;
  }

  Element render() override {
    Element alert = Element::create("div")
                        .addClass("flare-alert")
                        .addClass("flare-alert-" + type);

    // Icon
    String icon = "ℹ️";
    if (type == "success")
      icon = "✅";
    else if (type == "warning")
      icon = "⚠️";
    else if (type == "danger")
      icon = "🚨";

    Element header = Element::create("div").addClass("flare-alert-header");
    header.addChild(
        Element::create("span").addClass("flare-alert-icon").text(icon));
    header.addChild(
        Element::create("span").addClass("flare-alert-title").text(title));

    if (dismissible) {
      header.addChild(
          Element::create("span")
              .addClass("flare-alert-close")
              .text("✕")
              .onClick(
                  "this.parentElement.parentElement.style.display='none'"));
    }

    alert.addChild(header);

    if (message.length()) {
      alert.addChild(
          Element::create("div").addClass("flare-alert-message").text(message));
    }

    return alert;
  }

  static String css() {
    return ".flare-alert{"
           "padding:14px 18px;"
           "border-radius:10px;"
           "margin:12px 0;"
           "border-left:4px solid;"
           "}"
           ".flare-alert-header{"
           "display:flex;"
           "align-items:center;"
           "gap:8px;"
           "}"
           ".flare-alert-icon{font-size:16px;}"
           ".flare-alert-title{font-weight:600;font-size:14px;flex:1;}"
           ".flare-alert-close{"
           "cursor:pointer;"
           "opacity:0.5;"
           "font-size:14px;"
           "transition:opacity 0.2s;"
           "}"
           ".flare-alert-close:hover{opacity:1;}"
           ".flare-alert-message{"
           "margin-top:8px;"
           "font-size:13px;"
           "opacity:0.85;"
           "padding-left:26px;"
           "}"
           ".flare-alert-info{background:rgba(59,130,246,0.08);border-color:#"
           "3b82f6;color:#93c5fd;}"
           ".flare-alert-success{background:rgba(34,197,94,0.08);border-color:#"
           "22c55e;color:#86efac;}"
           ".flare-alert-warning{background:rgba(245,158,11,0.08);border-color:"
           "#f59e0b;color:#fde68a;}"
           ".flare-alert-danger{background:rgba(239,68,68,0.08);border-color:#"
           "ef4444;color:#fca5a5;}";
  }
};
