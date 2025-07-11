#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <Arduino.h>

struct SensorReadEvent {
  int id;
  String deviceId;
  String recordType;
  float value;

  SensorReadEvent(int eventId, const String& dId, const String& rType, float val)
    : id(eventId), deviceId(dId), recordType(rType), value(val) {}
};

class EventHandler {
public:
    virtual void on(const SensorReadEvent& event) = 0;
    virtual ~EventHandler() = default;
};

#endif