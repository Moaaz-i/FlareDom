#pragma once
#include "../Component.h"

class Toast : public Component {
public:
    Element render() override {
        // Container element
        Element el = Element::create("div").attr("id", "toast-container");
        el.style.position("fixed").add("bottom:20px").add("right:20px").add("z-index:9999")
                 .display("flex").flexDirection("column").gap("10px");
        
        // Append JS utility script
        Element scr = Element::create("script").text(
            "window.toast = function(msg, type='success') {"
            "  const c = document.getElementById('toast-container');"
            "  if (!c) return;"
            "  const t = document.createElement('div');"
            "  t.innerText = msg;"
            "  t.style.padding = '12px 20px';"
            "  t.style.borderRadius = '8px';"
            "  t.style.color = '#fff';"
            "  t.style.fontSize = '14px';"
            "  t.style.fontWeight = '500';"
            "  t.style.boxShadow = '0 4px 12px rgba(0,0,0,0.15)';"
            "  t.style.transition = 'all 0.3s ease';"
            "  t.style.opacity = '0';"
            "  t.style.transform = 'translateY(20px)';"
            "  if (type === 'success') t.style.background = 'var(--success, #22c55e)';"
            "  else if (type === 'danger') t.style.background = 'var(--danger, #ef4444)';"
            "  else t.style.background = 'var(--accent, #3b82f6)';"
            "  c.appendChild(t);"
            "  setTimeout(() => { t.style.opacity = '1'; t.style.transform = 'translateY(0)'; }, 50);"
            "  setTimeout(() => {"
            "    t.style.opacity = '0';"
            "    t.style.transform = 'translateY(-20px)';"
            "    setTimeout(() => t.remove(), 300);"
            "  }, 3000);"
            "};"
        );
        el.addChild(scr);
        return el;
    }
};
