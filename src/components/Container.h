#pragma once
#include "../Component.h"

// Feature 17: Flex/Grid Container layout helper
class Container : public Component {
private:
    String layoutType;
    String gapVal = "16px";
    String justifyVal;
    String alignVal;
    String colsVal;
    bool wrapEnabled = false;
    String maxWidthVal;
    String paddingVal = "20px";
    std::vector<Element> items;

public:
    Container(const String &layout = "flex") : layoutType(layout) {}

    Container &gap(const String &g) { gapVal = g; return *this; }
    Container &justify(const String &j) { justifyVal = j; return *this; }
    Container &align(const String &a) { alignVal = a; return *this; }
    Container &wrap(bool w) { wrapEnabled = w; return *this; }
    Container &maxWidth(const String &mw) { maxWidthVal = mw; return *this; }
    Container &padding(const String &p) { paddingVal = p; return *this; }

    Container &columns(int n) {
        colsVal = "";
        for (int i = 0; i < n; i++) {
            if (i > 0) colsVal += " ";
            colsVal += "1fr";
        }
        return *this;
    }

    Container &columnsCustom(const String &cols) {
        colsVal = cols;
        return *this;
    }

    Container &add(const Element &el) {
        items.push_back(el);
        return *this;
    }

    Element render() override {
        Element container = Element::create("div").addClass("flare-container");

        container.style
            .display(layoutType)
            .gap(gapVal)
            .padding(paddingVal);

        if (justifyVal.length()) container.style.justifyContent(justifyVal);
        if (alignVal.length()) container.style.alignItems(alignVal);
        if (maxWidthVal.length()) {
            container.style.maxWidth(maxWidthVal).add("margin:0 auto");
        }

        if (layoutType == "flex") {
            if (wrapEnabled) container.style.add("flex-wrap:wrap");
        } else if (layoutType == "grid") {
            if (colsVal.length()) {
                container.style.gridTemplateColumns(colsVal);
            }
        }

        for (auto &item : items) {
            container.addChild(item);
        }

        return container;
    }
};
