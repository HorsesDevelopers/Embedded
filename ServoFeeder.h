#pragma once
#include <ESP32Servo.h>
#include <Arduino.h>

class ServoFeeder {
public:
    ServoFeeder(int pin) : pin(pin) {}

    void begin() {
        servo.setPeriodHertz(50);
        servo.attach(pin, 500, 2400);
        servo.write(0); 
    }

    void feed(const String& duration) {
        int openAngle = 90; 
        int closeAngle = 0; 
        int timeMs = getDurationMs(duration);

        Serial.printf("🦐 Alimentando peces (%s, %d ms)...\n", duration.c_str(), timeMs);
        servo.write(openAngle);
        delay(timeMs);
        servo.write(closeAngle);
        Serial.println("✅ Alimentación completada.");
    }

    void reset() {
        servo.write(0);
    }

private:
    int pin;
    Servo servo;

    int getDurationMs(const String& duration) {
        if (duration == "SHORT") return 3000;
        if (duration == "MEDIUM") return 5000;
        if (duration == "LONG") return 7000;
        return 3000; // Default
    }
};
