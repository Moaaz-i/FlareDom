<p align="center">
  <img src="https://img.shields.io/badge/🔥-FlareDom-FF6B35?style=for-the-badge&labelColor=1a1a2e" alt="FlareDom" />
</p>

<h1 align="center">FlareDom</h1>

<p align="center">
  <strong>⚡ Build stunning HTML interfaces on ESP8266/ESP32 — entirely from C++</strong>
</p>

<p align="center">
  <a href="https://github.com/Moaaz-i/FlareDom/releases"><img src="https://img.shields.io/github/v/release/Moaaz-i/FlareDom?style=flat-square&color=00ff88&labelColor=0d1117" alt="Release" /></a>
  <a href="https://github.com/Moaaz-i/FlareDom/blob/main/LICENSE"><img src="https://img.shields.io/github/license/Moaaz-i/FlareDom?style=flat-square&color=ff6b35&labelColor=0d1117" alt="License" /></a>
  <a href="https://www.arduino.cc/reference/en/libraries/"><img src="https://img.shields.io/badge/platform-ESP8266%20|%20ESP32-blue?style=flat-square&labelColor=0d1117" alt="Platform" /></a>
  <a href="#"><img src="https://img.shields.io/badge/language-C++-f34b7d?style=flat-square&labelColor=0d1117" alt="C++" /></a>
</p>

<br />

<p align="center">
  FlareDom is a lightweight C++ UI framework that lets you build dynamic, responsive web dashboards and interfaces directly on your ESP8266/ESP32 — <b>no HTML files, no SPIFFS, no frontend toolchain.</b> Just pure C++ components that render beautiful HTML.
</p>

---

## ✨ Why FlareDom?

| Pain Point | FlareDom Solution |
|---|---|
| Writing raw HTML strings in `server.send()` | **Component-based** — build UI like building blocks |
| Managing messy string concatenation | **Fluent API** — chainable methods for clean code |
| No routing, no structure | **Built-in Router** — multi-page apps with one line |
| Inline styles everywhere | **Style system** — global CSS + per-element styles |
| No JS management | **ScriptManager** — inject & organize JavaScript cleanly |
| No HTML minification | **HtmlBuilder** — auto-minified output for faster loads |

---

## 🏗️ Architecture

```
FlareDom
├── Core
│   ├── Element         — Virtual DOM node with fluent API
│   ├── Page            — Full HTML document container
│   ├── Style           — CSS rule builder
│   ├── Component       — Abstract base for reusable widgets
│   └── IDGen           — Auto-generated unique element IDs
│
├── Engine
│   ├── HtmlBuilder     — Renders & minifies final HTML
│   ├── Router          — URL-to-Page mapping with 404 support
│   └── ScriptManager   — JavaScript injection & event binding
│
└── Widgets
    ├── Card            — Dashboard header card
    ├── Gauge           — SVG circular gauge (animated)
    └── StatusPanel     — Status display with dynamic text
```

---

## 🚀 Quick Start

### Installation

**Arduino Library Manager (Recommended):**
1. Open Arduino IDE → **Sketch** → **Include Library** → **Manage Libraries**
2. Search for `FlareDom`
3. Click **Install**

**Manual Installation:**
```bash
cd ~/Documents/Arduino/libraries
git clone https://github.com/Moaaz-i/FlareDom.git
```

### Minimal Example

```cpp
#include <ESP8266WebServer.h>
#include <FlareDom.h>

ESP8266WebServer server(80);

Page buildPage() {
    Page p("My Page");

    p.setGlobalCSS(
        "body { background: #111; color: #fff; font-family: Consolas; "
        "text-align: center; padding-top: 50px; }"
        ".box { padding: 20px; background: #222; border-radius: 12px; "
        "display: inline-block; }"
    );

    Element box = Element::create("div").addClass("box");
    box.addChild(Element::create("h1").text("Hello FlareDom!"));
    box.addChild(Element::create("p").text("Built entirely in C++"));

    p.add(box);
    return p;
}

void setup() {
    Serial.begin(115200);
    WiFi.begin("YOUR_SSID", "YOUR_PASSWORD");
    while (WiFi.status() != WL_CONNECTED) delay(200);

    server.on("/", []() {
        Page p = buildPage();
        server.send(200, "text/html", HtmlBuilder::build(p));
    });

    server.begin();
    Serial.println("Server started: http://" + WiFi.localIP().toString());
}

void loop() {
    server.handleClient();
}
```

---

## 📖 API Reference

### `Element` — The Building Block

Every UI piece is an `Element`. Create, style, nest — all with a fluent API.

```cpp
// Create any HTML element
Element div = Element::create("div");

// Chain methods fluently
Element card = Element::create("div")
    .addClass("card")
    .attr("id", "main-card")
    .text("Hello World");

// Nest elements
Element container = Element::create("div");
container.addChild(Element::create("h1").text("Title"));
container.addChild(Element::create("p").text("Description"));

// Inline styles
Element styled = Element::create("div");
styled.style.add("background: #222");
styled.style.add("border-radius: 12px");
styled.style.add("padding: 20px");

// Auto-generate unique IDs
Element el = Element::create("span").ensureId("sensor");
// → id="sensor1", id="sensor2", ...
```

| Method | Description |
|---|---|
| `Element::create(tag)` | Create a new element with the given HTML tag |
| `.text(content)` | Set the inner text content |
| `.attr(name, value)` | Set an HTML attribute |
| `.addClass(className)` | Add a CSS class (supports multiple calls) |
| `.addChild(element)` | Append a child element |
| `.ensureId(prefix)` | Auto-assign a unique ID if none exists |
| `.style.add(rule)` | Add an inline CSS rule |
| `.render()` | Generate the HTML string |

---

### `Page` — The Document

A `Page` wraps elements into a full HTML5 document with `<!DOCTYPE>`, `<head>`, and `<body>`.

```cpp
Page p("Dashboard");

// Global CSS applies to the entire page
p.setGlobalCSS(
    "body { background: #0a0a0a; color: #fff; }"
    "h1 { color: #00ff88; }"
);

// Add elements to the page body
p.add(Element::create("h1").text("Welcome"));
p.add(myComponent.render());

// Render the complete HTML document
String html = p.render();
```

---

### `Component` — Reusable Widgets

Extend `Component` to create reusable, self-contained UI pieces.

```cpp
class TemperatureCard : public Component {
private:
    String label;
    float value;

public:
    TemperatureCard(const String &l, float v) : label(l), value(v) {}

    Element render() override {
        Element card = Element::create("div").addClass("temp-card");
        card.addChild(Element::create("h3").text(label));
        card.addChild(Element::create("span")
            .addClass("value")
            .text(String(value) + "°C"));
        return card;
    }
};

// Usage
TemperatureCard temp("Room Temp", 23.5);
p.add(temp.render());
```

**Built-in Components:**

| Component | Description |
|---|---|
| `Card(title)` | Dashboard header card with branding |
| `Gauge()` | SVG circular gauge with animated arc |
| `StatusPanel()` | Status display with dynamic color-coded text |

---

### `Router` — Multi-Page Apps

Map URL paths to page-building functions — with automatic HTML rendering and minification.

```cpp
ESP8266WebServer server(80);
Router router(&server);

router.addRoute("/", homePage);
router.addRoute("/settings", settingsPage);
router.addRoute("/sensors", sensorsPage);

// Custom 404 page
router.setNotFound([]() {
    Page p("404");
    p.add(Element::create("h1").text("Page Not Found"));
    return p;
});
```

---

### `ScriptManager` — JavaScript Injection

Manage client-side JavaScript without messy string concatenation.

```cpp
ScriptManager sm;

// Add raw JavaScript
sm.add("console.log('FlareDom loaded');");

// Add named functions
sm.addFunction("refresh", "location.reload();");

// Bind DOM events
sm.addEvent("#btn", "click", "alert('Clicked!');");

// Render as a <script> element and add to page
p.add(sm.render());
```

---

### `HtmlBuilder` — Optimized Output

Minify and build the final HTML for efficient transmission over WiFi.

```cpp
Page p = buildDashboard();

// Minified (default) — removes whitespace for smaller payload
String html = HtmlBuilder::build(p);

// Pretty-printed — useful for debugging
String debug = HtmlBuilder::build(p, false);
```

---

## 🎯 Examples

The library ships with 3 ready-to-use examples:

| Example | Description | Key Features |
|---|---|---|
| [**BasicExample**](examples/BasicExample/BasicExample.ino) | Simple styled page | Elements, CSS, HtmlBuilder |
| [**DashboardExample**](examples/DashboardExample/DashboardExample.ino) | Live sensor dashboard | Gauge, StatusPanel, ScriptManager, AJAX |
| [**RouterExample**](examples/RouterExample/RouterExample.ino) | Multi-page navigation | Router, 404 handler, page linking |

Open them from Arduino IDE: **File** → **Examples** → **FlareDom**

---

## 🔧 Compatibility

| Board | Status |
|---|---|
| ESP8266 (NodeMCU, Wemos D1, etc.) | ✅ Fully Supported |
| ESP32 | ✅ Supported (use `<WebServer.h>` instead of `<ESP8266WebServer.h>`) |

**Requirements:**
- Arduino IDE 1.8+ or PlatformIO
- ESP8266 / ESP32 board package installed
- C++11 or later (default for ESP cores)

---

## 🤝 Contributing

Contributions are welcome! Whether it's new components, bug fixes, or documentation improvements:

1. **Fork** the repository
2. **Create** your feature branch (`git checkout -b feature/awesome-widget`)
3. **Commit** your changes (`git commit -m 'Add awesome widget component'`)
4. **Push** to the branch (`git push origin feature/awesome-widget`)
5. **Open** a Pull Request

---

## 📄 License

This project is open source. See the [LICENSE](LICENSE) file for details.

---

<p align="center">
  <sub>Built with ❤️ for the Arduino & ESP community</sub>
</p>
