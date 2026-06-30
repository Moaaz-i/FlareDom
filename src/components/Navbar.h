#pragma once
#include "../Component.h"
#include <vector>

// Feature 11: Navigation Bar
class Navbar : public Component {
private:
    String brand;
    struct NavLink {
        String href;
        String label;
    };
    std::vector<NavLink> links;

public:
    Navbar(const String &b) : brand(b) {}

    Navbar &addLink(const String &href, const String &label) {
        links.push_back({href, label});
        return *this;
    }

    Element render() override {
        Element nav = Element::create("nav").addClass("flare-navbar");

        nav.addChild(
            Element::create("a")
                .addClass("flare-navbar-brand")
                .attr("href", "/")
                .text(brand)
        );

        Element menu = Element::create("div").addClass("flare-navbar-links");
        for (const auto &link : links) {
            menu.addChild(
                Element::create("a")
                    .addClass("flare-navbar-link")
                    .attr("href", link.href)
                    .text(link.label)
            );
        }

        nav.addChild(menu);
        return nav;
    }

    static String css() {
        return
            ".flare-navbar{"
                "display:flex;"
                "align-items:center;"
                "justify-content:space-between;"
                "padding:12px 24px;"
                "background:rgba(15,23,42,0.9);"
                "backdrop-filter:blur(12px);"
                "border-bottom:1px solid rgba(255,255,255,0.08);"
                "position:sticky;"
                "top:0;"
                "z-index:100;"
            "}"
            ".flare-navbar-brand{"
                "font-size:18px;"
                "font-weight:700;"
                "color:#fff;"
                "text-decoration:none;"
            "}"
            ".flare-navbar-links{"
                "display:flex;"
                "gap:8px;"
            "}"
            ".flare-navbar-link{"
                "color:#94a3b8;"
                "text-decoration:none;"
                "padding:6px 14px;"
                "border-radius:6px;"
                "font-size:14px;"
                "transition:all 0.2s ease;"
            "}"
            ".flare-navbar-link:hover{"
                "color:#fff;"
                "background:rgba(255,255,255,0.08);"
            "}";
    }
};
