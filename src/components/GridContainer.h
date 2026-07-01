#pragma once
#include "../Component.h"

class GridContainer : public Component {
private:
  std::vector<Element> items;
  String minItemWidth;
  String spacing;

public:
  GridContainer(const String &minWidth = "280px",
                const String &gapSize = "20px")
      : minItemWidth(minWidth), spacing(gapSize) {}

  GridContainer &add(const Element &item) {
    items.push_back(item);
    return *this;
  }

  Element render() override {
    Element grid = Element::create("div");
    grid.style.display("grid")
        .gridTemplateColumns("repeat(auto-fit, minmax(" + minItemWidth +
                             ", 1fr))")
        .gap(spacing);

    for (auto &item : items) {
      grid.addChild(item);
    }

    return grid;
  }
};
