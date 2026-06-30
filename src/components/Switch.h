#pragma once
#include "../Component.h"
#include "../IDGen.h"

// Feature 15: Toggle Switch
class Switch : public Component {
private:
    String name;
    bool checked;
    String onChangeHandler;
    String switchId;

public:
    Switch(const String &n, bool initial = false)
        : name(n), checked(initial) {
        switchId = IDGen::next("sw");
    }

    Switch &onChange(const String &handler) {
        onChangeHandler = handler;
        return *this;
    }

    String getId() const { return switchId; }

    Element render() override {
        Element wrapper = Element::create("label").addClass("flare-switch");

        Element input = Element::create("input")
            .attr("type", "checkbox")
            .attr("name", name)
            .attr("id", switchId)
            .addClass("flare-switch-input");

        if (checked) input.attr("checked", "checked");
        if (onChangeHandler.length()) input.onEvent("change", onChangeHandler);

        Element slider = Element::create("span").addClass("flare-switch-slider");

        wrapper.addChild(input);
        wrapper.addChild(slider);

        return wrapper;
    }

    static String css() {
        return
            ".flare-switch{"
                "position:relative;"
                "display:inline-block;"
                "width:48px;"
                "height:26px;"
                "cursor:pointer;"
            "}"
            ".flare-switch-input{"
                "opacity:0;"
                "width:0;"
                "height:0;"
                "position:absolute;"
            "}"
            ".flare-switch-slider{"
                "position:absolute;"
                "top:0;left:0;right:0;bottom:0;"
                "background:rgba(255,255,255,0.12);"
                "border-radius:26px;"
                "transition:all 0.3s cubic-bezier(0.4,0,0.2,1);"
            "}"
            ".flare-switch-slider::before{"
                "content:'';"
                "position:absolute;"
                "height:20px;"
                "width:20px;"
                "left:3px;"
                "bottom:3px;"
                "background:#fff;"
                "border-radius:50%;"
                "transition:all 0.3s cubic-bezier(0.4,0,0.2,1);"
            "}"
            ".flare-switch-input:checked + .flare-switch-slider{"
                "background:#3b82f6;"
            "}"
            ".flare-switch-input:checked + .flare-switch-slider::before{"
                "transform:translateX(22px);"
            "}";
    }
};
