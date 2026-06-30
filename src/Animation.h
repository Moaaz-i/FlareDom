#pragma once
#include <Arduino.h>

// Feature 7: CSS Animation (Keyframes)
struct Animation {
    String name;
    String keyframes;

    Animation(const String &n, const String &kf) : name(n), keyframes(kf) {}

    String toCSS() const {
        return "@keyframes " + name + "{" + keyframes + "}";
    }
};
