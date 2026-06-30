# FlareDom

A UI Framework for ESP8266/ESP32 written in C++.

## Features

- HTML rendering
- Components system
- CSS injection
- JavaScript support
- Dynamic dashboards
- Routing system
- Widgets library

## Example

#include <FlareDom.h>

Page p("Demo");
Card c("Hello World");
p.add(c.render());
