#pragma once

#define PH_PIN      34
#define O2_PIN      35
#define TEMP_PIN    15
#define SERVO_PIN   26

#define READ_INTERVAL   1000
#define FEED_INTERVAL   5000

#define MAC_ADRESS 

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASS ""

// Edge server config
#define DEVICE_ID      "pond-001"
#define EDGE_IP        "192.168.110.104"
#define EDGE_PORT      5000
#define EDGE_API_KEY   "test-api-key-123"

// MQTT config
#define MQTT_SERVER    "192.168.110.104"  
#define MQTT_PORT      1884
#define MQTT_TOPIC_SUB "feed/command"
#define MQTT_TOPIC_PUB "feed/command/completed"