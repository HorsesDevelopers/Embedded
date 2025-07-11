#ifndef POND_EVENT_HANDLER_H
#define POND_EVENT_HANDLER_H

#include <HTTPClient.h>
#include "ModestIoTConfig.h"

class PondEventHandler {
public:
  void sendSensorData(const String& deviceId, float temp, float ph, float turbidity, const String& createdAt = "") {
    if (WiFi.status() != WL_CONNECTED) return;

    String url = String("http://") + EDGE_IP + ":" + String(EDGE_PORT) + "/api/v1/pond-monitoring/data-records/batch";

    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-API-Key", EDGE_API_KEY);

    String json = "{\"device_id\":\"" + deviceId +
                  "\",\"temp\":" + String(temp, 2) +
                  ",\"ph\":" + String(ph, 2) +
                  ",\"turbidity\":" + String(turbidity, 2);
    if (createdAt != "") {
      json += ",\"created_at\":\"" + createdAt + "\"";
    }
    json += "}";

    int httpResponseCode = http.POST(json);
    if (httpResponseCode > 0) {
      Serial.println(http.getString());
    } else {
      Serial.printf("Error al enviar datos: %d\n", httpResponseCode);
    }
    http.end();
  }
};

#endif