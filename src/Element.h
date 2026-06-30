#pragma once
#include <Arduino.h>
#include <vector>
#include <map>
#include "Style.h"
#include "IDGen.h"

class Element {
private:
    String tag;
    String innerText;
    std::map<String, String> attrs;
    Style styleObj;
    std::vector<Element> children;
    String idStr;

public:
    Element(const String &t) : tag(t) {}

    static Element create(const String &tag) {
        return Element(tag);
    }

    Style &style = styleObj;

    Element &text(const String &t) {
        innerText = t;
        return *this;
    }

    Element &attr(const String &name, const String &value) {
        attrs[name] = value;
        return *this;
    }

    Element &addClass(const String &cls) {
        if (attrs.count("class")) {
            attrs["class"] += " " + cls;
        } else {
            attrs["class"] = cls;
        }
        return *this;
    }

    Element &addChild(const Element &child) {
        children.push_back(child);
        return *this;
    }

    Element &ensureId(const String &prefix = "el") {
        if (!idStr.length()) {
            idStr = IDGen::next(prefix);
            attr("id", idStr);
        }
        return *this;
    }

    String render() {   // ← أزلنا const هنا
        if (tag == "script") {
            String s = "<script>";
            s += innerText;
            s += "</script>";
            return s;
        }

        String s = "<" + tag;

        String styleStr = styleObj.toString();
        if (styleStr.length()) {
            attrs["style"] = styleStr;
        }

        for (auto &kv : attrs) {
            s += " " + kv.first + "=\"" + kv.second + "\"";
        }

        s += ">";

        s += innerText;

        for (auto &child : children) {
            s += child.render();
        }

        s += "</" + tag + ">";
        return s;
    }
};
