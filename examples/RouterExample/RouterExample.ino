#include <ESP8266WebServer.h>
#include <FlareDom.h>

ESP8266WebServer server(80);
Router router(&server);

Page homePage() {
    Page p("Home page");

    p.setGlobalCSS("body{background:#000;color:#fff;font-family:Consolas;text-align:center;padding-top:40px;}");

    Element h = Element::create("h1").text("This is home page");
    Element link = Element::create("a").attr("href", "/settings").text("Go to settings page");

    p.add(h);
    p.add(link);

    return p;
}

Page settingsPage() {
    Page p("Settings page");

    p.setGlobalCSS("body{background:#111;color:#fff;font-family:Consolas;text-align:center;padding-top:40px;}");

    Element h = Element::create("h1").text("Settings page");
    Element link = Element::create("a").attr("href", "/").text("Back");

    p.add(h);
    p.add(link);

    return p;
}

void setup() {
    Serial.begin(115200);

    WiFi.begin("SSID", "PASSWORD");
    while (WiFi.status() != WL_CONNECTED) delay(200);

    router.addRoute("/", homePage);
    router.addRoute("/settings", settingsPage);

    router.setNotFound([](){
        Page p("404");
        p.add(Element::create("h1").text("Page not found"));
        return p;
    });

    server.begin();
}

void loop() {
    server.handleClient();
}
