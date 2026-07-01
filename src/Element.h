#pragma once
#include "IDGen.h"
#include "Style.h"
#include <Arduino.h>
#include <functional>
#include <map>
#include <vector>

// Global map to hold variable bindings for automatic route generation
inline std::map<String, std::function<String()>> &getGlobalDynamicRoutes() {
  static std::map<String, std::function<String()>> routes;
  return routes;
}

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

  // Flash-based properties (PROGMEM) to minimize RAM usage
  const __FlashStringHelper *flashTag = nullptr;
  const __FlashStringHelper *flashText = nullptr;
  const __FlashStringHelper *flashHtml = nullptr;

  void initSelfClosing(const String &t) {
    if (t == "input" || t == "br" || t == "hr" || t == "img" || t == "meta" ||
        t == "link") {
      isSelfClosing = true;
    }
  }

  Element &addBindScript(const String &route) {
    Element script = Element::create("script");
    String js = "(function(){"
                "  const el = document.getElementById('" +
                idStr +
                "');"
                "  if(!el) return;"
                "  const update = async () => {"
                "    try {"
                "      let r = await fetch('" +
                route +
                "');"
                "      if(r.ok) {"
                "        let txt = await r.text();"
                "        if(el.tagName === 'INPUT' || el.tagName === "
                "'TEXTAREA' || el.tagName === 'SELECT') {"
                "          if(el.value !== txt) el.value = txt;"
                "        } else {"
                "          if(el.innerText !== txt) el.innerText = txt;"
                "        }"
                "      }"
                "    } catch(e) {}"
                "  };"
                "  setInterval(update, 1000);"
                "})();";
    script.text(js);
    addChild(script);
    return *this;
  }

public:
  Element(const String &t) : tag(t) { initSelfClosing(t); }

  Element(const __FlashStringHelper *t) : flashTag(t) {
    initSelfClosing(String(t));
  }

  static Element create(const String &tag) { return Element(tag); }

  static Element create(const __FlashStringHelper *tag) { return Element(tag); }

  // FontAwesome Icon Helper
  static Element icon(const String &iconClass) {
    return Element::create("i").addClass(iconClass);
  }

  Style &style = styleObj;

  // ─── Text & Content ───

  Element &text(const String &t) {
    innerText = t;
    flashText = nullptr;
    return *this;
  }

  Element &text(const __FlashStringHelper *t) {
    flashText = t;
    innerText = "";
    return *this;
  }

  Element &html(const String &h) {
    rawHtml = h;
    flashHtml = nullptr;
    return *this;
  }

  Element &html(const __FlashStringHelper *h) {
    flashHtml = h;
    rawHtml = "";
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

  Element &onClick(const String &handler) {
    attrs["onclick"] = handler;
    return *this;
  }

  Element &data(const String &key, const String &value) {
    attrs["data-" + key] = value;
    return *this;
  }

  Element &disabled() {
    attrs["disabled"] = "disabled";
    return *this;
  }

  Element &readonly() {
    attrs["readonly"] = "readonly";
    return *this;
  }

  Element &tooltip(const String &tip) {
    attrs["title"] = tip;
    return *this;
  }

  Element &onEvent(const String &event, const String &handler) {
    attrs["on" + event] = handler;
    return *this;
  }

  // ─── Variable Bindings ───

  Element &bindValue(int *val, const String &route) {
    ensureId("bind");
    getGlobalDynamicRoutes()[route] = [val]() { return String(*val); };
    return addBindScript(route);
  }

  Element &bindValue(float *val, const String &route, int decimals = 2) {
    ensureId("bind");
    getGlobalDynamicRoutes()[route] = [val, decimals]() {
      return String(*val, decimals);
    };
    return addBindScript(route);
  }

  Element &bindValue(double *val, const String &route, int decimals = 4) {
    ensureId("bind");
    getGlobalDynamicRoutes()[route] = [val, decimals]() {
      return String(*val, decimals);
    };
    return addBindScript(route);
  }

  Element &bindValue(String *val, const String &route) {
    ensureId("bind");
    getGlobalDynamicRoutes()[route] = [val]() { return *val; };
    return addBindScript(route);
  }

  Element &bindValue(bool *val, const String &route) {
    ensureId("bind");
    getGlobalDynamicRoutes()[route] = [val]() {
      return *val ? "true" : "false";
    };
    return addBindScript(route);
  }

  Element &bindValue(std::function<String()> cb, const String &route) {
    ensureId("bind");
    getGlobalDynamicRoutes()[route] = cb;
    return addBindScript(route);
  }

  // ─── Local Storage Sync Helper ───
  Element &syncLocalStorage(const String &key) {
    ensureId("ls");
    Element script = Element::create("script");
    String js =
        "(function() {"
        "  const el = document.getElementById('" +
        idStr +
        "');"
        "  if (!el) return;"
        "  const saved = localStorage.getItem('" +
        key +
        "');"
        "  if (saved !== null) {"
        "    if (el.tagName === 'INPUT' || el.tagName === 'TEXTAREA' || "
        "el.tagName === 'SELECT') el.value = saved;"
        "    else el.innerText = saved;"
        "  }"
        "  const save = () => {"
        "    const val = (el.tagName === 'INPUT' || el.tagName === 'TEXTAREA' "
        "|| el.tagName === 'SELECT') ? el.value : el.innerText;"
        "    localStorage.setItem('" +
        key +
        "', val);"
        "  };"
        "  el.addEventListener('input', save);"
        "  el.addEventListener('change', save);"
        "  const observer = new MutationObserver(save);"
        "  observer.observe(el, { childList: true, characterData: true, "
        "subtree: true });"
        "})();";
    script.text(js);
    addChild(script);
    return *this;
  }

  // ─── WebSocket Client Sender helper ───
  Element &onClickSendWs(const String &wsName, const String &cmd,
                         const String &payload = "") {
    ensureId("ws-send");
    // Trigger command on websocket object.
    // Assuming websocket object is available globally as wsName
    return onClick(wsName + ".send('" + cmd + ":" + payload + "')");
  }

  // ─── Form AJAX Submit Helper ───
  Element &ajaxSubmit(const String &endpoint, const String &onSuccessJS = "") {
    ensureId("form-ajax");
    return onEvent("submit",
                   "event.preventDefault();"
                   "const data = new FormData(this);"
                   "fetch('" +
                       endpoint +
                       "', { method: 'POST', body: data })"
                       ".then(r => r.text())"
                       ".then(res => {"
                       "  if(" +
                       String(onSuccessJS.length() ? "true" : "false") + ") {" +
                       onSuccessJS +
                       "  }"
                       "}).catch(e => console.error(e));");
  }

  // ─── Render ───

  void renderTo(String &out) {
    if (flashTag) {
      String tagStr(flashTag);
      if (tagStr == "script") {
        out += "<script>";
        if (flashText)
          out += flashText;
        else
          out += innerText;
        out += "</script>";
        return;
      }
    } else if (tag == "script") {
      out += "<script>";
      if (flashText)
        out += flashText;
      else
        out += innerText;
      out += "</script>";
      return;
    }

    out += "<";
    if (flashTag)
      out += flashTag;
    else
      out += tag;

    String styleStr = styleObj.toString();
    if (styleStr.length()) {
      attrs["style"] = styleStr;
    }

    for (auto &kv : attrs) {
      if (kv.first == "disabled" || kv.first == "readonly" ||
          kv.first == "checked" || kv.first == "required" ||
          kv.first == "autofocus") {
        out += " " + kv.first;
      } else {
        out += " " + kv.first + "=\"" + kv.second + "\"";
      }
    }

    if (isSelfClosing) {
      out += " />";
      return;
    }

    out += ">";

    if (flashHtml) {
      out += flashHtml;
    } else if (rawHtml.length()) {
      out += rawHtml;
    } else if (flashText) {
      out += flashText;
    } else {
      out += innerText;
    }

    for (auto &child : children) {
      child.renderTo(out);
    }

    out += "</";
    if (flashTag)
      out += flashTag;
    else
      out += tag;
    out += ">";
  }

  String render() {
    String s = "";
    s.reserve(512);
    renderTo(s);
    return s;
  }
};
