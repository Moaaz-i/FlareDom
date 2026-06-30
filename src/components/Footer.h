#pragma once
#include "../Component.h"
#include <vector>

// Feature 16: Page Footer
class Footer : public Component {
private:
  String copyright;
  struct FooterLink {
    String label;
    String url;
  };
  std::vector<FooterLink> links;

public:
  Footer(const String &copy) : copyright(copy) {}

  Footer &addLink(const String &label, const String &url) {
    links.push_back({label, url});
    return *this;
  }

  Element render() override {
    Element footer = Element::create("footer").addClass("flare-footer");

    if (links.size()) {
      Element nav = Element::create("div").addClass("flare-footer-links");
      for (const auto &link : links) {
        nav.addChild(Element::create("a")
                         .addClass("flare-footer-link")
                         .attr("href", link.url)
                         .attr("target", "_blank")
                         .text(link.label));
      }
      footer.addChild(nav);
    }

    footer.addChild(
        Element::create("div").addClass("flare-footer-copy").text(copyright));

    return footer;
  }

  static String css() {
    return ".flare-footer{"
           "padding:24px;"
           "text-align:center;"
           "border-top:1px solid rgba(255,255,255,0.06);"
           "margin-top:40px;"
           "}"
           ".flare-footer-links{"
           "display:flex;"
           "justify-content:center;"
           "gap:16px;"
           "margin-bottom:12px;"
           "flex-wrap:wrap;"
           "}"
           ".flare-footer-link{"
           "color:#64748b;"
           "text-decoration:none;"
           "font-size:13px;"
           "transition:color 0.2s;"
           "}"
           ".flare-footer-link:hover{color:#e2e8f0;}"
           ".flare-footer-copy{"
           "color:#475569;"
           "font-size:12px;"
           "}";
  }
};
