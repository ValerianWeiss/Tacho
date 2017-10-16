#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_MILLIS 4294967295
#define BAUD_RATE 115200
#define Pi 3.14159

#define SESSION_ACTIVE 1
#define SESSION_NOT_ACTIVE 0
#define ARDUINO_STARTS_SENDING "startSending"

typedef enum sessionType{
  SESSION,
  BIKE_SESSION,
};

#endif
