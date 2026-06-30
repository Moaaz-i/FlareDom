#include <ESPAsyncWebServer.h>
#include <FlareDom.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

AsyncWebServer server(80);
Router router(&server);

Page homePage() {
  Page p("Home page");
  p.setGlobalCSS(ThemeManager::dark());

  Element container = Element::create("div");
  container.style.textAlign("center").padding("40px");

  Element h = Element::create("h1").text("This is home page");
  Element link = Element::create("a")
                     .attr("href", "/settings")
                     .text("Go to settings page");

  container.addChild(h);
  container.addChild(link);
  p.add(container);

  return p;
}

Page settingsPage() {
  Page p("Settings page");
  p.setGlobalCSS(ThemeManager::dark());

  Element container = Element::create("div");
  container.style.textAlign("center").padding("40px");

  Element h = Element::create("h1").text("Settings page");
  Element link = Element::create("a").attr("href", "/").text("Back");

  container.addChild(h);
  container.addChild(link);
  p.add(container);

  return p;
}

void setup() {
  Serial.begin(115200);

  WiFi.begin("SSID", "PASSWORD");
  while (WiFi.status() != WL_CONNECTED)
    delay(200);

  router.addRoute("/", homePage);
  router.addRoute("/settings", settingsPage);

  router.setNotFound([]() {
    Page p("404");
    p.setGlobalCSS(ThemeManager::dark());
    p.add(Element::create("h1").text("Page not found"));
    return p;
  });

  server.begin();
}

void loop() {
  // Async server handles clients internally!
}
