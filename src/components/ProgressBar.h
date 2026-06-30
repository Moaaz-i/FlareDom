#pragma once
#include "../Component.h"

// Feature 12: Progress Bar with animated fill
class ProgressBar : public Component {
private:
    int value;
    String variant = "primary";
    String label;
    String barId;
    bool showLabel = true;

public:
    ProgressBar(int v, const String &var = "primary")
        : value(v), variant(var) {
        barId = IDGen::next("pb");
    }

    ProgressBar &setLabel(const String &l) {
        label = l;
        showLabel = true;
        return *this;
    }

    ProgressBar &hideLabel() {
        showLabel = false;
        return *this;
    }

    String getId() const { return barId; }

    Element render() override {
        Element wrapper = Element::create("div").addClass("flare-progress-wrapper");

        if (showLabel) {
            Element header = Element::create("div").addClass("flare-progress-header");
            header.addChild(
                Element::create("span")
                    .addClass("flare-progress-label")
                    .text(label.length() ? label : variant)
            );
            header.addChild(
                Element::create("span")
                    .addClass("flare-progress-value")
                    .attr("id", barId + "-text")
                    .text(String(value) + "%")
            );
            wrapper.addChild(header);
        }

        Element track = Element::create("div").addClass("flare-progress-track");

        Element bar = Element::create("div")
            .addClass("flare-progress-bar")
            .addClass("flare-progress-" + variant)
            .attr("id", barId);
        bar.style.width(String(value) + "%");

        track.addChild(bar);
        wrapper.addChild(track);
        return wrapper;
    }

    static String css() {
        return
            ".flare-progress-wrapper{margin:12px 0;}"
            ".flare-progress-header{"
                "display:flex;"
                "justify-content:space-between;"
                "margin-bottom:6px;"
                "font-size:13px;"
            "}"
            ".flare-progress-label{color:#94a3b8;text-transform:capitalize;}"
            ".flare-progress-value{color:#e2e8f0;font-weight:600;}"
            ".flare-progress-track{"
                "width:100%;"
                "height:8px;"
                "background:rgba(255,255,255,0.08);"
                "border-radius:99px;"
                "overflow:hidden;"
            "}"
            ".flare-progress-bar{"
                "height:100%;"
                "border-radius:99px;"
                "transition:width 0.6s cubic-bezier(0.4,0,0.2,1);"
            "}"
            ".flare-progress-primary{background:linear-gradient(90deg,#3b82f6,#60a5fa);}"
            ".flare-progress-success{background:linear-gradient(90deg,#22c55e,#4ade80);}"
            ".flare-progress-danger{background:linear-gradient(90deg,#ef4444,#f87171);}"
            ".flare-progress-warning{background:linear-gradient(90deg,#f59e0b,#fbbf24);}";
    }
};
