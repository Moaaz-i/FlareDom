#pragma once
#include <Arduino.h>

struct Style {
    String raw;

    Style &add(const String &rule) {
        if (raw.length()) raw += ";";
        raw += rule;
        return *this;
    }

    String toString() const {
        return raw;
    }
};
