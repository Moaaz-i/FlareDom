#pragma once
#include "../Component.h"

class ThemeToggler : public Component {
public:
  Element render() override {
    Element btn = Element::create("button")
                      .addClass("theme-toggler-btn")
                      .attr("id", "themeToggler")
                      .html("🌓 Toggle Theme");

    btn.style.padding("10px 20px")
        .radius("8px")
        .border("1px solid var(--border, rgba(255,255,255,0.15))")
        .bg("var(--bg-secondary, #1f2937)")
        .color("var(--text-primary, #ffffff)")
        .cursor("pointer")
        .fontWeight("600")
        .transition("all 0.3s ease");

    Element script = Element::create("script").text(
        "(function() {"
        "  const btn = document.getElementById('themeToggler');"
        "  if(!btn) return;"
        "  const themes = ['dark', 'light', 'neon', 'cyberpunk'];"
        "  let currentIdx = 0;"
        "  const applyTheme = (theme) => {"
        "    document.documentElement.setAttribute('data-theme', theme);"
        "    localStorage.setItem('flare-theme', theme);"
        "  };"
        "  const saved = localStorage.getItem('flare-theme');"
        "  if (saved) {"
        "    currentIdx = themes.indexOf(saved);"
        "    if (currentIdx === -1) currentIdx = 0;"
        "    applyTheme(themes[currentIdx]);"
        "  }"
        "  btn.addEventListener('click', () => {"
        "    currentIdx = (currentIdx + 1) % themes.length;"
        "    applyTheme(themes[currentIdx]);"
        "  });"
        "})();");

    Element container = Element::create("div");
    container.addChild(btn);
    container.addChild(script);
    return container;
  }
};
