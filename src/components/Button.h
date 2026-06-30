#pragma once
#include "../Component.h"

// Feature 8: Interactive Button with variants
class Button : public Component {
private:
    String label;
    String onClickHandler;
    String variant = "primary";

public:
    Button(const String &l, const String &handler = "")
        : label(l), onClickHandler(handler) {}

    Button &setVariant(const String &v) {
        variant = v;
        return *this;
    }

    Element render() override {
        Element btn = Element::create("button")
            .addClass("flare-btn")
            .addClass("flare-btn-" + variant)
            .text(label);

        if (onClickHandler.length()) {
            btn.onClick(onClickHandler);
        }

        return btn;
    }

    // Returns built-in CSS for all button variants
    static String css() {
        return
            ".flare-btn{"
                "padding:10px 24px;"
                "border:none;"
                "border-radius:8px;"
                "font-size:14px;"
                "font-weight:600;"
                "cursor:pointer;"
                "transition:all 0.2s ease;"
                "font-family:inherit;"
                "outline:none;"
            "}"
            ".flare-btn:hover{transform:translateY(-1px);filter:brightness(1.15);}"
            ".flare-btn:active{transform:translateY(0);filter:brightness(0.95);}"
            ".flare-btn-primary{background:#3b82f6;color:#fff;}"
            ".flare-btn-success{background:#22c55e;color:#fff;}"
            ".flare-btn-danger{background:#ef4444;color:#fff;}"
            ".flare-btn-warning{background:#f59e0b;color:#111;}"
            ".flare-btn-outline{background:transparent;color:#3b82f6;border:2px solid #3b82f6;}"
            ".flare-btn-ghost{background:transparent;color:#ccc;}"
            ".flare-btn-ghost:hover{background:rgba(255,255,255,0.08);}";
    }
};
