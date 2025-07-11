#pragma once
#include <WiFi.h>
#include "ModestIoTConfig.h"

class WifiManager {
public:
  void begin() {
    Serial.print("Conectando a WiFi");

    WiFi.begin(WIFI_SSID, WIFI_PASS, 6);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }

    Serial.println(" ✅ Conectado!");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
  }
};
