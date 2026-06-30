#include <ESPAsyncWebServer.h>
#include <FlareDom.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

AsyncWebServer server(80);
Router router(&server);

Page buildPage() {
    Page p("Basic Example");
    p.setGlobalCSS(ThemeManager::dark());

    Element box = Element::create("div");
    box.style.bg("var(--bg-secondary)").padding("30px").radius("16px")
       .display("inline-block").shadow("0 8px 32px rgba(0,0,0,0.3)");

    box.addChild(Element::create("h1").text("Hello to you in FlareDom"));
    box.addChild(Element::create("p").text("This is a simple asynchronous example."));

    p.add(box);
    return p;
}

void setup() {
    Serial.begin(115200);

    WiFi.begin("SSID", "PASSWORD");
    while (WiFi.status() != WL_CONNECTED) delay(200);

    router.addRoute("/", buildPage);

    server.begin();
}

void loop() {
    // No server.handleClient() needed for AsyncWebServer!
}
