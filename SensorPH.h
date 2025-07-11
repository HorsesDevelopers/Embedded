#pragma once
#include <Arduino.h>

class SensorPH {
public:
  SensorPH(int pin) : pin(pin) {
    pinMode(pin, INPUT);
  }

  float read() {
    int raw = analogRead(pin);
    return map(raw, 0, 4095, 0, 14);
  }

private:
  int pin;
};
