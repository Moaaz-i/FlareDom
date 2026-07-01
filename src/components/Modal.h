#pragma once
#include "../Component.h"

class Modal : public Component {
private:
    String elementId;
    String title;
    std::vector<Element> content;

public:
    Modal(const String &id, const String &t) : elementId(id), title(t) {}

    Modal &add(const Element &el) {
        content.push_back(el);
        return *this;
    }

    Element render() override {
        Element overlay = Element::create("div")
            .attr("id", elementId)
            .addClass("flare-modal-overlay");

        overlay.style.position("fixed")
            .add("top:0;left:0;right:0;bottom:0")
            .bg("rgba(0,0,0,0.5)")
            .add("backdrop-filter:blur(8px)")
            .display("none")
            .justifyContent("center")
            .alignItems("center")
            .add("z-index:999");

        Element box = Element::create("div").addClass("flare-modal-box");
        box.style.bg("var(--bg-card, #111827)")
            .padding("25px")
            .radius("16px")
            .width("90%")
            .maxWidth("500px")
            .border("1px solid var(--border, rgba(255,255,255,0.08))")
            .shadow("0 20px 25px -5px rgba(0,0,0,0.3)");

        Element header = Element::create("div");
        header.style.display("flex").justifyContent("space-between").alignItems("center").margin("0 0 15px 0");
        
        header.addChild(Element::create("h3").text(title));
        
        Element closeBtn = Element::create("button")
            .html("&times;")
            .onClick("document.getElementById('" + elementId + "').style.display='none'");
        closeBtn.style.bg("transparent")
            .border("none")
            .color("var(--text-secondary, #94a3b8)")
            .fontSize("24px")
            .cursor("pointer");
        
        header.addChild(closeBtn);
        box.addChild(header);

        Element body = Element::create("div");
        for (auto &el : content) {
            body.addChild(el);
        }
        box.addChild(body);

        overlay.addChild(box);

        Element script = Element::create("script").text(
            "window.openModal = function(id) {"
            "  const el = document.getElementById(id);"
            "  if(el) { el.style.display = 'flex'; }"
            "};"
            "window.closeModal = function(id) {"
            "  const el = document.getElementById(id);"
            "  if(el) { el.style.display = 'none'; }"
            "};"
        );
        overlay.addChild(script);

        return overlay;
    }
};
