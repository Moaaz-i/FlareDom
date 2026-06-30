#pragma once
#include <Arduino.h>

// Feature 18: Pre-built Theme System
class ThemeManager {
public:
    // Dark theme (default)
    static String dark() {
        return
            ":root{"
                "--bg-primary:#0a0a0f;"
                "--bg-secondary:#111827;"
                "--bg-card:rgba(17,24,39,0.8);"
                "--text-primary:#f1f5f9;"
                "--text-secondary:#94a3b8;"
                "--accent:#3b82f6;"
                "--accent-glow:rgba(59,130,246,0.15);"
                "--border:rgba(255,255,255,0.08);"
                "--success:#22c55e;"
                "--warning:#f59e0b;"
                "--danger:#ef4444;"
            "}"
            "*{margin:0;padding:0;box-sizing:border-box;}"
            "body{"
                "background:var(--bg-primary);"
                "color:var(--text-primary);"
                "font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,sans-serif;"
                "line-height:1.6;"
            "}"
            "a{color:var(--accent);text-decoration:none;}"
            "a:hover{text-decoration:underline;}";
    }

    // Light theme
    static String light() {
        return
            ":root{"
                "--bg-primary:#f8fafc;"
                "--bg-secondary:#ffffff;"
                "--bg-card:#ffffff;"
                "--text-primary:#0f172a;"
                "--text-secondary:#64748b;"
                "--accent:#2563eb;"
                "--accent-glow:rgba(37,99,235,0.1);"
                "--border:rgba(0,0,0,0.08);"
                "--success:#16a34a;"
                "--warning:#d97706;"
                "--danger:#dc2626;"
            "}"
            "*{margin:0;padding:0;box-sizing:border-box;}"
            "body{"
                "background:var(--bg-primary);"
                "color:var(--text-primary);"
                "font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,sans-serif;"
                "line-height:1.6;"
            "}"
            "a{color:var(--accent);text-decoration:none;}"
            "a:hover{text-decoration:underline;}";
    }

    // Neon / Cyberpunk green theme
    static String neon() {
        return
            ":root{"
                "--bg-primary:#050a0e;"
                "--bg-secondary:#0a1628;"
                "--bg-card:rgba(10,22,40,0.7);"
                "--text-primary:#e0f2fe;"
                "--text-secondary:#38bdf8;"
                "--accent:#00ff88;"
                "--accent-glow:rgba(0,255,136,0.12);"
                "--border:rgba(0,255,136,0.1);"
                "--success:#00ff88;"
                "--warning:#ffcc00;"
                "--danger:#ff3366;"
            "}"
            "*{margin:0;padding:0;box-sizing:border-box;}"
            "body{"
                "background:var(--bg-primary);"
                "color:var(--text-primary);"
                "font-family:'Consolas','Courier New',monospace;"
                "line-height:1.6;"
            "}"
            "a{color:var(--accent);text-decoration:none;}"
            "a:hover{text-shadow:0 0 8px var(--accent);}";
    }

    // Cyberpunk pink/purple theme
    static String cyberpunk() {
        return
            ":root{"
                "--bg-primary:#0d0221;"
                "--bg-secondary:#1a0533;"
                "--bg-card:rgba(26,5,51,0.7);"
                "--text-primary:#e8d5f5;"
                "--text-secondary:#c084fc;"
                "--accent:#f472b6;"
                "--accent-glow:rgba(244,114,182,0.15);"
                "--border:rgba(192,132,252,0.12);"
                "--success:#34d399;"
                "--warning:#fbbf24;"
                "--danger:#fb7185;"
            "}"
            "*{margin:0;padding:0;box-sizing:border-box;}"
            "body{"
                "background:var(--bg-primary);"
                "color:var(--text-primary);"
                "font-family:'Consolas','Courier New',monospace;"
                "line-height:1.6;"
                "background-image:radial-gradient(ellipse at 50% 0%,rgba(192,132,252,0.08) 0%,transparent 60%);"
            "}"
            "a{color:var(--accent);text-decoration:none;}"
            "a:hover{text-shadow:0 0 10px var(--accent);}";
    }
};
