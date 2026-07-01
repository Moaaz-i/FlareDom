#pragma once
#include "../Component.h"

class Spinner : public Component {
private:
    String size;
    String color;

public:
    Spinner(const String &sz = "30px", const String &clr = "var(--accent, #3b82f6)")
        : size(sz), color(clr) {}

    Element render() override {
        Element loader = Element::create("div").addClass("flare-spinner");
        loader.style.width(size)
              .height(size)
              .border("3px solid rgba(255,255,255,0.1)")
              .add("border-top: 3px solid " + color)
              .radius("50%")
              .display("inline-block")
              .add("animation: spin 1s linear infinite");
              
        Element style = Element::create("style").text(
            "@keyframes spin { 0% { transform: rotate(0deg); } 100% { transform: rotate(360deg); } }"
        );
        
        Element container = Element::create("span");
        container.style.display("inline-flex").alignItems("center").justifyContent("center");
        container.addChild(loader);
        container.addChild(style);
        return container;
    }
};
