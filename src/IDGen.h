#pragma once
#include <Arduino.h>

class IDGen {
private:
  static unsigned long counter;

public:
  static String next(const String &prefix = "el") {
    counter++;
    return prefix + String(counter);
  }
};

unsigned long IDGen::counter = 0;
