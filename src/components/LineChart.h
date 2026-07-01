#pragma once
#include "../Component.h"

class LineChart : public Component {
private:
  String elementId;
  String label;
  String dataEndpoint;

public:
  LineChart(const String &id, const String &lbl, const String &endpoint)
      : elementId(id), label(lbl), dataEndpoint(endpoint) {}

  Element render() override {
    Element canvas = Element::create("canvas").attr("id", elementId);
    canvas.style.maxWidth("100%").height("300px");

    Element container = Element::create("div");
    container.style.bg("var(--bg-card, rgba(17,24,39,0.8))")
        .padding("20px")
        .radius("12px")
        .border("1px solid var(--border, rgba(255,255,255,0.08))");
    container.addChild(canvas);

    Element script = Element::create("script").text(
        "(function() {"
        "  const initChart = () => {"
        "    const ctx = document.getElementById('" +
        elementId +
        "').getContext('2d');"
        "    const chart = new Chart(ctx, {"
        "      type: 'line',"
        "      data: {"
        "        labels: [],"
        "        datasets: [{"
        "          label: '" +
        label +
        "',"
        "          data: [],"
        "          borderColor: '#3b82f6',"
        "          backgroundColor: 'rgba(59,130,246,0.1)',"
        "          borderWidth: 2,"
        "          tension: 0.4,"
        "          fill: true"
        "        }]"
        "      },"
        "      options: {"
        "        responsive: true,"
        "        maintainAspectRatio: false,"
        "        scales: {"
        "          x: { grid: { color: 'rgba(255,255,255,0.05)' } },"
        "          y: { grid: { color: 'rgba(255,255,255,0.05)' } }"
        "        }"
        "      }"
        "    });"
        "    const update = async () => {"
        "      try {"
        "        let r = await fetch('" +
        dataEndpoint +
        "');"
        "        if (r.ok) {"
        "          let val = parseFloat(await r.text());"
        "          const time = new Date().toLocaleTimeString();"
        "          chart.data.labels.push(time);"
        "          chart.data.datasets[0].data.push(val);"
        "          if (chart.data.labels.length > 10) {"
        "            chart.data.labels.shift();"
        "            chart.data.datasets[0].data.shift();"
        "          }"
        "          chart.update();"
        "        }"
        "      } catch(e) {}"
        "    };"
        "    setInterval(update, 2000);"
        "  };"
        "  if (typeof Chart === 'undefined') {"
        "    const script = document.createElement('script');"
        "    script.src = 'https://cdn.jsdelivr.net/npm/chart.js';"
        "    script.onload = initChart;"
        "    document.head.appendChild(script);"
        "  } else {"
        "    initChart();"
        "  }"
        "})();");
    container.addChild(script);
    return container;
  }
};
