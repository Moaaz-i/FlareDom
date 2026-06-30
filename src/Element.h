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
    String rawHtml;
    std::map<String, String> attrs;
    Style styleObj;
    std::vector<Element> children;
    String idStr;
    bool isSelfClosing = false;

public:
    Element(const String &t) : tag(t) {
        // Self-closing tags
        if (t == "input" || t == "br" || t == "hr" || t == "img" ||
            t == "meta" || t == "link") {
            isSelfClosing = true;
        }
    }

    static Element create(const String &tag) {
        return Element(tag);
    }

    Style &style = styleObj;

    // ─── Text & Content ───

    Element &text(const String &t) {
        innerText = t;
        return *this;
    }

    // Feature 3: Raw HTML content
    Element &html(const String &h) {
        rawHtml = h;
        return *this;
    }

    // ─── Attributes ───

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

    // Feature 1: onClick handler
    Element &onClick(const String &handler) {
        attrs["onclick"] = handler;
        return *this;
    }

    // Feature 2: data-* attributes
    Element &data(const String &key, const String &value) {
        attrs["data-" + key] = value;
        return *this;
    }

    // Feature 4: disabled / readonly
    Element &disabled() {
        attrs["disabled"] = "disabled";
        return *this;
    }

    Element &readonly() {
        attrs["readonly"] = "readonly";
        return *this;
    }

    // Feature 5: tooltip (title attribute)
    Element &tooltip(const String &tip) {
        attrs["title"] = tip;
        return *this;
    }

    // Generic inline event handler
    Element &onEvent(const String &event, const String &handler) {
        attrs["on" + event] = handler;
        return *this;
    }

    // ─── Render ───

    String render() {
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
            if (kv.first == "disabled" || kv.first == "readonly" ||
                kv.first == "checked" || kv.first == "required" ||
                kv.first == "autofocus") {
                s += " " + kv.first;
            } else {
                s += " " + kv.first + "=\"" + kv.second + "\"";
            }
        }

        if (isSelfClosing) {
            s += " />";
            return s;
        }

        s += ">";

        if (rawHtml.length()) {
            s += rawHtml;
        } else {
            s += innerText;
        }

        for (auto &child : children) {
            s += child.render();
        }

        s += "</" + tag + ">";
        return s;
    }
};
