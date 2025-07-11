#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <Arduino.h>

/**
 * feeder command
 */
struct ServoCommand {
    int pondId;
    String duration; // "SHORT", "MEDIUM", "LONG"

    ServoCommand(int id, const String& dur) : pondId(id), duration(dur) {}
};

class CommandHandler {
public:
    virtual void handle(ServoCommand command) = 0;
    virtual ~CommandHandler() = default;
};

#endif