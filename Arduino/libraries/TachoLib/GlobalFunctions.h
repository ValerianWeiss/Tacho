#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

#include <Arduino.h>

class GlobalFunctions
{
  private:
    GlobalFunctions();

  public:
    static String getJsonMessage(String jsonMsg);
    static void readJsonFromSerial(String *messageBuffer);
};

#endif