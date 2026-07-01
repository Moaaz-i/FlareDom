#include <ESPAsyncWebServer.h>
#include <FlareDom.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

AsyncWebServer server(80);
Router router(&server);

int gasValue = 0;

Page dashboardPage() {
  Page p("Dashboard Example");

  // Enable modern premium features
  p.enableTailwind();
  p.addGoogleFont("Outfit");
  p.enableCustomScrollbar("#3b82f6", "#0f172a");
  p.setDescription("A premium IoT dashboard powered by FlareDom.");

  p.setGlobalCSS(":root{--neon-green:#00ff88;--neon-yellow:#ffcc00;--neon-red:#"
                 "ff3366;--current-color:var(--neon-green);} "
                 "body{background:#070a13;color:#fff;font-family:'Outfit',sans-"
                 "serif;text-align:center;padding-top:20px;} "
                 ".dashboard-card{background:rgba(20,26,44,0.6);padding:30px;"
                 "border-radius:20px;display:inline-block;} "
                 ".status-text{color:var(--current-color);font-size:20px;font-"
                 "weight:bold;} ");

  // Grid Container containing cards and gauges
  GridContainer grid("300px", "20px");

  Card header("Smart Monitor of Gas");

  // Create an element that dynamically binds to our C++ gasValue variable!
  // No manual routes or javascript required.
  Element liveDisplay = Element::create("div")
                            .addClass("status-text")
                            .bindValue(&gasValue, "/gas");

  Gauge gauge;
  StatusPanel status;
  ThemeToggler themeToggler;

  grid.add(header.render());
  grid.add(gauge.render());
  grid.add(status.render());
  grid.add(liveDisplay);
  grid.add(themeToggler.render());

  p.add(grid.render());

  // Inject support for toaster messages
  Toast toasts;
  p.add(toasts.render());

  ScriptManager sm;
  sm.add(
      "function updateStatus(val){"
      "   let circ=2*Math.PI*90;"
      "   let off=circ-(val/100)*circ;"
      "   const gb = document.getElementById('gaugeBar');"
      "   if (gb) gb.style.strokeDashoffset=off;"
      "   const sl = document.getElementById('statusLabel');"
      "   "
      "if(val<=30){document.documentElement.style.setProperty('--current-color'"
      ",'var(--neon-green)');"
      "     if(sl) sl.innerText='Safe and pure 🟢';}"
      "   else "
      "if(val<=50){document.documentElement.style.setProperty('--current-color'"
      ",'var(--neon-yellow)');"
      "     if(sl) sl.innerText='Warning: relative increase 🟡';}"
      "   "
      "else{document.documentElement.style.setProperty('--current-color','var(-"
      "-neon-red)');"
      "     if(sl) sl.innerText='Danger: gas leak! 🚨';"
      "     if(window.toast) window.toast('Gas Leakage Detected!', 'danger');"
      "   }"
      "}"
      // Watch for live display changes to trigger the gauge & toast alert
      "setInterval(function(){"
      "  const bindEl = document.querySelector('[id^=\"bind\"]');"
      "  if (bindEl) {"
      "    let v = parseInt(bindEl.innerText) || 0;"
      "    updateStatus(v);"
      "  }"
      "}, 200);");
  p.add(sm.render());

  return p;
}

void setup() {
  Serial.begin(115200);

  WiFi.begin("SSID", "PASSWORD");
  while (WiFi.status() != WL_CONNECTED)
    delay(200);

  // Setup HTTP Basic Auth Credentials
  router.setCredentials("admin", "password123");

  // Protect the dashboard route
  router.addRoute("/", dashboardPage, true);

  server.begin();
}

void loop() {
  // Generate simulated updates to gasValue
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 2000) {
    lastUpdate = millis();
    gasValue = random(0, 100);
  }
}
