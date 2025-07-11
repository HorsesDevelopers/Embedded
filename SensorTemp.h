#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>

class SensorTemp {
public:
  SensorTemp(int pin) : oneWire(pin), sensors(&oneWire) {}
  
  void begin() {
    sensors.begin();
  }

  float read() {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
  }

private:
  OneWire oneWire;
  DallasTemperature sensors;
};
