#include <ESP8266WebServer.h>
#include <FlareDom.h>

ESP8266WebServer server(80);
Router router(&server);

int gasValue = 0;

Page dashboardPage() {
    Page p("Dashboard Example");

    p.setGlobalCSS(
        ":root{--neon-green:#00ff88;--neon-yellow:#ffcc00;--neon-red:#ff3366;--current-color:var(--neon-green);} "
        "body{background:#070a13;color:#fff;font-family:Consolas;text-align:center;padding-top:20px;} "
        ".dashboard-card{background:rgba(20,26,44,0.6);padding:30px;border-radius:20px;display:inline-block;} "
        ".status-text{color:var(--current-color);font-size:20px;font-weight:bold;} "
    );

    Card header("Smart cursor of gas");
    Gauge gauge;
    StatusPanel status;

    p.add(header.render());
    p.add(gauge.render());
    p.add(status.render());

    ScriptManager sm;

    sm.add(
        "function updateGas(){"
        " fetch('/gas').then(r=>r.text()).then(v=>{"
        "   document.getElementById('gasVal').innerText=v.padStart(2,'0');"
        "   let val=parseInt(v);"
        "   let circ=2*Math.PI*90;"
        "   let off=circ-(val/100)*circ;"
        "   document.getElementById('gaugeBar').style.strokeDashoffset=off;"
        "   if(val<=30){document.documentElement.style.setProperty('--current-color','var(--neon-green)');"
        "     document.getElementById('statusLabel').innerText='Safe and pure 🟢';}"
        "   else if(val<=50){document.documentElement.style.setProperty('--current-color','var(--neon-yellow)');"
        "     document.getElementById('statusLabel').innerText='Warning: relative increase 🟡';}"
        "   else{document.documentElement.style.setProperty('--current-color','var(--neon-red)');"
        "     document.getElementById('statusLabel').innerText='Danger: gas leak! 🚨';}"
        " });"
        "}"
        "setInterval(updateGas, 500);"
    );

    p.add(sm.render());

    return p;
}

void setup() {
    Serial.begin(115200);

    WiFi.begin("SSID", "PASSWORD");
    while (WiFi.status() != WL_CONNECTED) delay(200);

    router.addRoute("/", dashboardPage);

    server.on("/gas", [](){
        gasValue = random(0, 100);
        server.send(200, "text/plain", String(gasValue));
    });

    server.begin();
}

void loop() {
    server.handleClient();
}
