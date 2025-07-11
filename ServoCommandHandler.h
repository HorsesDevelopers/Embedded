#ifndef SERVO_COMMAND_HANDLER_H
#define SERVO_COMMAND_HANDLER_H

#include "CommandHandler.h"
#include "ServoFeeder.h"

class ServoCommandHandler : public CommandHandler {
public:
    ServoCommandHandler(ServoFeeder& feeder) : feeder(feeder) {}

    void handle(ServoCommand command) override {
        feeder.feed(command.duration);
    }

private:
    ServoFeeder& feeder;
};

#endif