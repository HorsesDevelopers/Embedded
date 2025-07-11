#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <time.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "ModestIoTConfig.h"
#include "WifiManager.h"
#include "SensorPH.h"
#include "SensorO2.h"
#include "SensorTemp.h"
#include "ServoFeeder.h"
#include "EventHandler.h"
#include "PondEventHandler.h"
#include "CommandHandler.h"
#include "ServoFeeder.h"
#include "ServoCommandHandler.h" 

WifiManager wifi;
SensorPH sensorPH(PH_PIN);
SensorO2 sensorO2(O2_PIN);
SensorTemp sensorTemp(TEMP_PIN);
ServoFeeder feeder(SERVO_PIN);
WebServer server(80);
PondEventHandler pondEventHandler;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
ServoCommandHandler servoHandler(feeder);

unsigned long lastReadTime = 0;
unsigned long lastFeedTime = 0;


String getCurrentTimeISO8601() {
  time_t now;
  struct tm timeinfo;
  char buf[25];
  time(&now);
  gmtime_r(&now, &timeinfo); // UTC (si quieres local usa localtime_r)
  strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  return String(buf);
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<128> doc;
  DeserializationError error = deserializeJson(doc, payload, length);
  if (error) return;
  int pondId = doc["pondId"];
  String duration = doc["duration"].as<String>();

  ServoCommand cmd(pondId, duration);
  servoHandler.handle(cmd);

  // Publicar mensaje de completado
  StaticJsonDocument<64> msg;
  msg["pondId"] = pondId;
  msg["status"] = "COMPLETED";
  char out[64];
  serializeJson(msg, out);
  mqttClient.publish(MQTT_TOPIC_PUB, out);
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando a MQTT...");
    if (mqttClient.connect("ESP32Feeder")) {
      Serial.println("Conectado!");
      mqttClient.subscribe(MQTT_TOPIC_SUB);
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Reintentando en 5s...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  wifi.begin();
  sensorTemp.begin();
  feeder.begin();

  configTime(0, 0, "pool.ntp.org", "time.nist.gov"); // UTC por defecto

  // Espera a que se sincronice el tiempo
  Serial.print("Esperando sincronización NTP");
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    delay(100);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println(" ¡Hora sincronizada!");

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  Serial.println("🚀 Sistema IoT de estanque listo y escuchando comandos MQTT.");
}

void loop() {
  unsigned long now = millis();

  if (now - lastReadTime >= READ_INTERVAL) {
    float ph = sensorPH.read();
    float turbidity = sensorO2.read();
    float temp = sensorTemp.read();
    String timestamp = getCurrentTimeISO8601();

    pondEventHandler.sendSensorData(DEVICE_ID, temp, ph, turbidity, timestamp);

    lastReadTime = now;
  }

  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop();
}