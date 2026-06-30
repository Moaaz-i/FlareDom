#pragma once
#include "../Component.h"

class Card : public Component {
private:
  String title;

public:
  Card(const String &t) : title(t) {}

  Element render() override {
    Element card = Element::create("div")
                       .addClass("dashboard-card")
                       .attr("id", "dashCard");

    card.addChild(Element::create("div")
                      .addClass("brand-title")
                      .text("Telemetry System"));

    card.addChild(Element::create("h1").text(title));

    return card;
  }
};
