#pragma once
#include <Arduino.h>

class SensorO2 {
public:
  SensorO2(int pin) : pin(pin) {
    pinMode(pin, INPUT);
  }

  float read() {
    int raw = analogRead(pin);
    return map(raw, 0, 4095, 0, 100);
  }

private:
  int pin;
};


