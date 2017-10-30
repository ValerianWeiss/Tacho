#include "GlobalFunctions.h"
#include "Constants.h"

GlobalFunctions::GlobalFunctions() {}

String GlobalFunctions::getJsonMessage(String jsonMsg)
{
	int startIndex;
	int endIndex;

	startIndex = jsonMsg.indexOf('{');
	endIndex = jsonMsg.indexOf('}') + 1;

	if (startIndex == -1 || endIndex == -1)
	{
		return "";
	}
	return jsonMsg.substring(startIndex, endIndex);
}

void GlobalFunctions::readJsonFromSerial(String *bufferStirng)
{
	unsigned long timer = millis();
	while (millis() - timer <= READING_TIME && getJsonMessage(*bufferStirng) == "")
	{
		*bufferStirng += Serial.readString();
	}
}