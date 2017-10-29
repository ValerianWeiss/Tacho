#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_MILLIS 4294967295
#define BAUD_RATE 115200
#define Pi 3.14159

#define SESSION_ACTIVE 1
#define SESSION_NOT_ACTIVE 0

#define MSG_STATUS_OK "{\"status\":\"0\"}"
#define MSG_NO_BODY_IN_REQUEST "{\"status\":\"-1\"}"
#define MSG_NO_RESPONSE_FROM_ARDUINO "{\"status\":\"-2\"}"
#define MSG_SESSION_NOT_ACTIVE "{\"status\":\"-3\"}"
#define MSG_SESSION_ALREADY_ACTIVE "{\"status\":\"-4\"}"

#define READING_TIME 100

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
