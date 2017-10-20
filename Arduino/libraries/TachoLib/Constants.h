#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_MILLIS 4294967295
#define BAUD_RATE 115200
#define Pi 3.14159

#define SESSION_ACTIVE 1
#define SESSION_NOT_ACTIVE 0

enum sessionCommand{
  START_COMMAND,
  STOP_COMMAND,
  PAUSE_COMMAND
};

enum sessionType{
  SESSION,
  BIKE_SESSION,
};

#endif
