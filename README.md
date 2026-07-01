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
  <a href="#"><img src="https://img.shields.io/badge/components-13+-8b5cf6?style=flat-square&labelColor=0d1117" alt="Components" /></a>
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
| Inline styles everywhere | **Style system** — 25+ CSS shortcuts + themes |
| No JS management | **ScriptManager** — inject & organize JavaScript cleanly |
| No HTML minification | **HtmlBuilder** — auto-minified output for faster loads |
| Repetitive AJAX polling code | **LiveValue** — auto-updating values in one line |
| Designing from scratch every time | **ThemeManager** — 4 pre-built themes ready to use |

---

## 🏗️ Architecture

```
FlareDom v2.0.0
├── Core
│   ├── Element         — Virtual DOM node with fluent API
│   ├── Page            — Full HTML5 document (meta, favicon, external CSS, lang)
│   ├── Style           — CSS rule builder with 25+ shortcut methods
│   ├── Animation       — CSS @keyframes definitions
│   ├── Component       — Abstract base for reusable widgets
│   └── IDGen           — Auto-generated unique element IDs
│
├── Engine
│   ├── HtmlBuilder     — Renders & minifies final HTML
│   ├── Router          — URL-to-Page mapping using ESPAsyncWebServer
│   ├── ScriptManager   — JavaScript injection & event binding
│   ├── ThemeManager    — Pre-built themes (dark, light, neon, cyberpunk)
│   ├── LiveValue       — Auto-updating AJAX values
│   └── WebSocketValue  — Real-time WebSocket updates
```

---

## 🚀 Quick Start

### Installation

**Dependencies:**
This library requires:
- `ESPAsyncWebServer`
- `ESPAsyncTCP` (for ESP8266) or `AsyncTCP` (for ESP32)

**Arduino Library Manager (Recommended):**
1. Open Arduino IDE → **Sketch** → **Include Library** → **Manage Libraries**
2. Search for `FlareDom`
3. Click **Install** (and install the dependencies if prompted)

**Manual Installation:**
```bash
cd ~/Documents/Arduino/libraries
git clone https://github.com/Moaaz-i/FlareDom.git
```

### Minimal Example

```cpp
#include <ESPAsyncWebServer.h>
#include <FlareDom.h>

AsyncWebServer server(80);
Router router(&server);

Page buildPage() {
    Page p("My Page");
    p.setGlobalCSS(ThemeManager::dark());

    Element box = Element::create("div");
    box.style.bg("#1e293b").padding("30px").radius("16px")
       .display("inline-block").shadow("0 8px 32px rgba(0,0,0,0.3)");

    box.addChild(Element::create("h1").text("Hello FlareDom!"));
    box.addChild(Element::create("p").text("Built entirely in C++ with ESPAsyncWebServer"));

    p.add(box);
    return p;
}

void setup() {
    Serial.begin(115200);
    WiFi.begin("YOUR_SSID", "YOUR_PASSWORD");
    while (WiFi.status() != WL_CONNECTED) delay(200);

    router.addRoute("/", buildPage);

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

// Style shortcuts (NEW in v1.1)
Element styled = Element::create("div");
styled.style.bg("#222").color("#fff").padding("20px").radius("12px");

// Click handler (NEW in v1.1)
Element btn = Element::create("button")
    .text("Click Me")
    .onClick("alert('Hello!')");

// Data attributes (NEW in v1.1)
Element sensor = Element::create("div")
    .data("sensor", "temp")
    .data("value", "25.5");

// Raw HTML content (NEW in v1.1)
Element rich = Element::create("div")
    .html("<b>Bold</b> and <i>italic</i>");

// Tooltip (NEW in v1.1)
Element tip = Element::create("span")
    .text("Hover me")
    .tooltip("More info here");

// Auto-generate unique IDs
Element el = Element::create("span").ensureId("sensor");
// → id="sensor1", id="sensor2", ...
```

| Method | Description |
|---|---|
| `Element::create(tag)` | Create a new element with the given HTML tag |
| `.text(content)` | Set the inner text content |
| `.html(rawHtml)` | Set raw HTML content *(v1.1)* |
| `.attr(name, value)` | Set an HTML attribute |
| `.addClass(className)` | Add a CSS class (supports multiple calls) |
| `.addChild(element)` | Append a child element |
| `.ensureId(prefix)` | Auto-assign a unique ID if none exists |
| `.onClick(handler)` | Set inline click handler *(v1.1)* |
| `.onEvent(event, handler)` | Set any inline event handler *(v1.1)* |
| `.data(key, value)` | Set a `data-*` attribute *(v1.1)* |
| `.disabled()` | Mark element as disabled *(v1.1)* |
| `.readonly()` | Mark element as readonly *(v1.1)* |
| `.tooltip(text)` | Add a tooltip (title attribute) *(v1.1)* |
| `.style.add(rule)` | Add an inline CSS rule |
| `.render()` | Generate the HTML string |

---

### `Style` — CSS Shortcuts *(v1.1)*

Chain CSS properties with clean shortcut methods instead of writing raw strings.

```cpp
Element card = Element::create("div");
card.style
    .bg("#1e293b")
    .color("#f1f5f9")
    .padding("24px")
    .margin("16px")
    .radius("16px")
    .fontSize("14px")
    .border("1px solid rgba(255,255,255,0.1)")
    .shadow("0 4px 24px rgba(0,0,0,0.2)")
    .transition("all 0.3s ease")
    .display("flex")
    .gap("12px")
    .justifyContent("center")
    .alignItems("center");
```

<details>
<summary><b>All 25 style shortcuts</b></summary>

| Method | CSS Property |
|---|---|
| `.bg(val)` | `background` |
| `.color(val)` | `color` |
| `.padding(val)` | `padding` |
| `.margin(val)` | `margin` |
| `.radius(val)` | `border-radius` |
| `.fontSize(val)` | `font-size` |
| `.fontWeight(val)` | `font-weight` |
| `.border(val)` | `border` |
| `.width(val)` | `width` |
| `.height(val)` | `height` |
| `.maxWidth(val)` | `max-width` |
| `.minHeight(val)` | `min-height` |
| `.display(val)` | `display` |
| `.textAlign(val)` | `text-align` |
| `.opacity(val)` | `opacity` |
| `.cursor(val)` | `cursor` |
| `.shadow(val)` | `box-shadow` |
| `.transition(val)` | `transition` |
| `.overflow(val)` | `overflow` |
| `.position(val)` | `position` |
| `.gap(val)` | `gap` |
| `.flexDirection(val)` | `flex-direction` |
| `.justifyContent(val)` | `justify-content` |
| `.alignItems(val)` | `align-items` |
| `.gridTemplateColumns(val)` | `grid-template-columns` |

</details>

---

### `Page` — The Document

A `Page` wraps elements into a full HTML5 document with `<!DOCTYPE>`, `<head>`, and `<body>`.

```cpp
Page p("Dashboard");

// Apply a pre-built theme (NEW in v1.1)
p.setGlobalCSS(ThemeManager::dark());

// Add custom CSS on top
p.appendCSS("h1 { color: #00ff88; }");

// Set language (auto-detects RTL) (NEW in v1.1)
p.setLang("en");  // → dir="ltr"
p.setLang("ar");  // → dir="rtl"

// Meta tags (NEW in v1.1)
p.addMeta("description", "My IoT Dashboard");
p.addMeta("author", "Moaaz");

// External CSS (NEW in v1.1)
p.addExternalCSS("https://fonts.googleapis.com/css2?family=Inter");

// Favicon (NEW in v1.1)
p.addFavicon("https://example.com/icon.png");

// CSS Animations (NEW in v1.1)
Animation fadeIn("fadeIn", "from{opacity:0}to{opacity:1}");
p.addAnimation(fadeIn);

// Add elements
p.add(Element::create("h1").text("Welcome"));

// Render the complete HTML document
String html = p.render();
```

---

### `ThemeManager` — Pre-built Themes *(v1.1)*

Four professionally designed themes with CSS custom properties.

```cpp
// Apply any theme with one line
p.setGlobalCSS(ThemeManager::dark());      // Clean dark mode
p.setGlobalCSS(ThemeManager::light());     // Clean light mode
p.setGlobalCSS(ThemeManager::neon());      // Green neon / hacker
p.setGlobalCSS(ThemeManager::cyberpunk()); // Pink/purple cyberpunk
```

Each theme provides CSS variables: `--bg-primary`, `--bg-secondary`, `--bg-card`, `--text-primary`, `--text-secondary`, `--accent`, `--accent-glow`, `--border`, `--success`, `--warning`, `--danger`.

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

---

### Built-in Components

#### Original Components

| Component | Description |
|---|---|
| `Card(title)` | Dashboard header card with branding |
| `Gauge()` | SVG circular gauge with animated arc |
| `StatusPanel()` | Status display with dynamic color-coded text |

#### New Components *(v1.1)*

**`Button`** — Interactive buttons with 6 variants:
```cpp
Button btn("Submit", "handleSubmit()");
btn.setVariant("primary"); // primary, success, danger, warning, outline, ghost
p.appendCSS(Button::css());
p.add(btn.render());
```

**`Table`** — Dynamic HTML tables:
```cpp
Table t;
t.setHeaders({"Name", "Value", "Status"});
t.addRow({"Temperature", "25°C", "Normal"});
t.addRow({"Humidity", "60%", "OK"});
p.appendCSS(Table::css());
p.add(t.render());
```

**`Input`** — Form fields with labels:
```cpp
Input nameField("text", "username", "Enter your name");
nameField.setLabel("Username").required();
p.appendCSS(Input::css());
p.add(nameField.render());
```

**`Navbar`** — Sticky navigation bar:
```cpp
Navbar nav("FlareDom");
nav.addLink("/", "Home");
nav.addLink("/settings", "Settings");
nav.addLink("/about", "About");
p.appendCSS(Navbar::css());
p.add(nav.render());
```

**`ProgressBar`** — Animated progress bars:
```cpp
ProgressBar pb(75, "success"); // 75%, green gradient
pb.setLabel("Upload Progress");
p.appendCSS(ProgressBar::css());
p.add(pb.render());
```

**`Badge`** — Status indicators:
```cpp
Badge online("Online", "success");   // success, warning, danger, info, neutral
p.appendCSS(Badge::css());
p.add(online.render());
```

**`AlertBox`** — Notification boxes:
```cpp
AlertBox alert("success", "Connected!", "All sensors are online.");
alert.setDismissible(true);
p.appendCSS(AlertBox::css());
p.add(alert.render());
```

**`Switch`** — Toggle switches:
```cpp
Switch sw("darkMode", true);
sw.onChange("toggleTheme()");
p.appendCSS(Switch::css());
p.add(sw.render());
```

**`Footer`** — Page footer:
```cpp
Footer f("© 2026 My Project");
f.addLink("GitHub", "https://github.com/...");
f.addLink("Docs", "/docs");
p.appendCSS(Footer::css());
p.add(f.render());
```

**`Container`** — Flex/Grid layout:
```cpp
// Flex layout
Container row("flex");
row.gap("20px").justify("center").wrap(true);
row.add(card1.render());
row.add(card2.render());
p.add(row.render());

// Grid layout
Container grid("grid");
grid.columns(3).gap("16px").maxWidth("900px");
grid.add(widget1);
grid.add(widget2);
grid.add(widget3);
p.add(grid.render());
```

---

### `LiveValue` — Auto-Updating Values *(v1.1)*

Fetch values from an endpoint and auto-update the display — with one line.

```cpp
LiveValue temp("/api/temp", "tempDisplay", 1000); // endpoint, elementId, ms
temp.suffix("°C");

p.appendCSS(LiveValue::css());
p.add(temp.render());   // The display element
p.add(temp.script());   // The auto-fetch script
```

On the server side:
```cpp
server.on("/api/temp", []() {
    float t = readTemperature();
    server.send(200, "text/plain", String(t));
});
```

---

### `Animation` — CSS Keyframes *(v1.1)*

Define CSS animations and apply them to elements.

```cpp
Animation fadeIn("fadeIn", "from{opacity:0}to{opacity:1}");
Animation pulse("pulse", "0%{transform:scale(1)}50%{transform:scale(1.05)}100%{transform:scale(1)}");

p.addAnimation(fadeIn);
p.addAnimation(pulse);

Element box = Element::create("div");
box.style.add("animation: fadeIn 0.5s ease, pulse 2s infinite");
```

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

## 📋 Changelog

### v1.1.0 — 20 New Features
- **Element**: `onClick()`, `onEvent()`, `data()`, `html()`, `disabled()`, `readonly()`, `tooltip()`, self-closing tag support
- **Style**: 25 CSS shortcut methods (`bg()`, `color()`, `padding()`, `radius()`, `shadow()`, etc.)
- **Animation**: CSS `@keyframes` system
- **Page**: `addMeta()`, `addExternalCSS()`, `addFavicon()`, `setLang()` (auto RTL), `appendCSS()`, `addAnimation()`
- **ThemeManager**: 4 pre-built themes (dark, light, neon, cyberpunk) with CSS custom properties
- **LiveValue**: Auto-updating AJAX values with `prefix()`/`suffix()` formatting
- **New Components**: Button, Table, Input, Navbar, ProgressBar, Badge, AlertBox, Switch, Footer, Container

### v1.0.0 — Initial Release
- Core: Element, Page, Style, Component, IDGen
- Engine: HtmlBuilder, ScriptManager, Router
- Widgets: Card, Gauge, StatusPanel

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
