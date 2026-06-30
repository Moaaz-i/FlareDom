#include <ESP8266WebServer.h>
#include <FlareDom.h>

ESP8266WebServer server(80);

Page buildPage() {
    Page p("Basic Example");

    p.setGlobalCSS(
        "body{background:#111;color:#fff;font-family:Consolas;text-align:center;padding-top:50px;}"
        ".box{padding:20px;background:#222;border-radius:12px;display:inline-block;}"
    );

    Element box = Element::create("div").addClass("box");
    box.addChild(Element::create("h1").text("Hello to you in FlareDom"));
    box.addChild(Element::create("p").text("This is a simple example of a page built with the library."));

    p.add(box);

    return p;
}

void setup() {
    Serial.begin(115200);

    WiFi.begin("SSID", "PASSWORD");
    while (WiFi.status() != WL_CONNECTED) delay(200);

    server.on("/", [](){
        Page p = buildPage();
        String html = HtmlBuilder::build(p);
        server.send(200, "text/html", html);
    });

    server.begin();
}

void loop() {
    server.handleClient();
}
