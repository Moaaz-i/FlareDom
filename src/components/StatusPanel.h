#pragma once
#include "../Component.h"

class StatusPanel : public Component {
public:
    Element render() override {
        Element panel = Element::create("div").addClass("status-panel");

        panel.addChild(Element::create("div")
            .addClass("status-title")
            .text("حالة البيئة الحالية"));

        panel.addChild(Element::create("div")
            .addClass("status-text")
            .attr("id","statusLabel")
            .text("آمن ونقي"));

        return panel;
    }
};
