#pragma once
#include "../Component.h"
#include <vector>

// Feature 9: Dynamic Table builder
class Table : public Component {
private:
  std::vector<String> headers;
  std::vector<std::vector<String>> rows;
  bool striped = true;

public:
  Table() {}

  Table &setHeaders(const std::vector<String> &h) {
    headers = h;
    return *this;
  }

  Table &addRow(const std::vector<String> &row) {
    rows.push_back(row);
    return *this;
  }

  Table &setStriped(bool s) {
    striped = s;
    return *this;
  }

  Element render() override {
    Element table = Element::create("table").addClass("flare-table");

    if (striped)
      table.addClass("flare-table-striped");

    // Header
    if (headers.size()) {
      Element thead = Element::create("thead");
      Element tr = Element::create("tr");
      for (const auto &h : headers) {
        tr.addChild(Element::create("th").text(h));
      }
      thead.addChild(tr);
      table.addChild(thead);
    }

    // Body
    Element tbody = Element::create("tbody");
    for (const auto &row : rows) {
      Element tr = Element::create("tr");
      for (const auto &cell : row) {
        tr.addChild(Element::create("td").text(cell));
      }
      tbody.addChild(tr);
    }
    table.addChild(tbody);

    return table;
  }

  static String css() {
    return ".flare-table{"
           "width:100%;"
           "border-collapse:collapse;"
           "border-radius:12px;"
           "overflow:hidden;"
           "font-size:14px;"
           "}"
           ".flare-table th{"
           "background:rgba(255,255,255,0.08);"
           "padding:12px 16px;"
           "text-align:left;"
           "font-weight:600;"
           "text-transform:uppercase;"
           "font-size:12px;"
           "letter-spacing:0.5px;"
           "color:#94a3b8;"
           "}"
           ".flare-table td{"
           "padding:10px 16px;"
           "border-top:1px solid rgba(255,255,255,0.06);"
           "}"
           ".flare-table-striped tbody tr:nth-child(even){"
           "background:rgba(255,255,255,0.03);"
           "}"
           ".flare-table tbody tr:hover{"
           "background:rgba(255,255,255,0.06);"
           "}";
  }
};
