#pragma once
#include "../Component.h"

class Gauge : public Component {
public:
    Element render() override {
        Element gauge = Element::create("div").addClass("gauge-container");

        Element svg = Element::create("svg").attr("viewBox", "0 0 200 200");

        svg.addChild(Element::create("circle")
            .addClass("bg-circle")
            .attr("cx","100").attr("cy","100").attr("r","90"));

        svg.addChild(Element::create("circle")
            .addClass("data-circle")
            .attr("id","gaugeBar")
            .attr("cx","100").attr("cy","100").attr("r","90"));

        Element box = Element::create("div").addClass("gauge-value-box");

        box.addChild(Element::create("div")
            .addClass("number")
            .attr("id","gasVal")
            .text("00"));

        box.addChild(Element::create("div")
            .addClass("unit")
            .text("RPM %"));

        gauge.addChild(svg);
        gauge.addChild(box);

        return gauge;
    }
};
