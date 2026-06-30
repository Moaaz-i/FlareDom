#include <ESPAsyncWebServer.h>
#include <FlareDom.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

AsyncWebServer server(80);
Router router(&server);
AsyncWebSocket ws("/ws");

int gasValue = 0;

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
               AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
    client->text(String(gasValue));
  }
}

Page dashboardPage() {
  Page p("Dashboard Example");

  p.setGlobalCSS(":root{--neon-green:#00ff88;--neon-yellow:#ffcc00;--neon-red:#"
                 "ff3366;--current-color:var(--neon-green);} "
                 "body{background:#070a13;color:#fff;font-family:Consolas;text-"
                 "align:center;padding-top:20px;} "
                 ".dashboard-card{background:rgba(20,26,44,0.6);padding:30px;"
                 "border-radius:20px;display:inline-block;} "
                 ".status-text{color:var(--current-color);font-size:20px;font-"
                 "weight:bold;} ");

  Card header("Smart cursor of gas");
  Gauge gauge;
  StatusPanel status;

  p.add(header.render());
  p.add(gauge.render());
  p.add(status.render());

  // Use WebSocketValue instead of LiveValue for real-time updates!
  WebSocketValue liveGas("ws://" + WiFi.localIP().toString() + "/ws", "gasVal");
  p.add(liveGas.render());
  p.add(liveGas.script());

  ScriptManager sm;
  sm.add("function updateStatus(val){"
         "   let circ=2*Math.PI*90;"
         "   let off=circ-(val/100)*circ;"
         "   document.getElementById('gaugeBar').style.strokeDashoffset=off;"
         "   "
         "if(val<=30){document.documentElement.style.setProperty('--current-"
         "color','var(--neon-green)');"
         "     document.getElementById('statusLabel').innerText='Safe and pure "
         "🟢';}"
         "   else "
         "if(val<=50){document.documentElement.style.setProperty('--current-"
         "color','var(--neon-yellow)');"
         "     document.getElementById('statusLabel').innerText='Warning: "
         "relative increase 🟡';}"
         "   "
         "else{document.documentElement.style.setProperty('--current-color','"
         "var(--neon-red)');"
         "     document.getElementById('statusLabel').innerText='Danger: gas "
         "leak! 🚨';}"
         "}"
         // Set up mutation observer or callback hook in socket logic if needed,
         // or poll local DOM value:
         "setInterval(function(){"
         "  let v = parseInt(document.getElementById('gasVal').innerText) || 0;"
         "  updateStatus(v);"
         "}, 200);");
  p.add(sm.render());

  return p;
}

void setup() {
  Serial.begin(115200);

  WiFi.begin("SSID", "PASSWORD");
  while (WiFi.status() != WL_CONNECTED)
    delay(200);

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  router.addRoute("/", dashboardPage);

  server.begin();
}

void loop() {
  ws.cleanupClients();

  // Broadcast updates every 2 seconds
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 2000) {
    lastUpdate = millis();
    gasValue = random(0, 100);
    ws.textAll(String(gasValue));
  }
}
