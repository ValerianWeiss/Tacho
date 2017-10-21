#include "SessionController.h"
#include "BikeSession.h"
#include "Session.h"
#include "Constants.h"
#include <ArduinoJson.h>

SessionController* SessionController::sessionController = NULL;
Session* SessionController::session = NULL;

SessionController::SessionController(){}


SessionController * SessionController::getInstance(){
  if(sessionController == NULL){
    sessionController = new SessionController();
  }
  return sessionController;
}

//This func should be called by the listenToSignal function
//TODO Add args [] for differet Session types (e.g wheel hight for BikeSession)
void SessionController::startSession(sessionType type, JsonObject& params){
	if(!this->session->getSessionState()){
		String* paramArray = getParams(params);

		switch(type){
			case SESSION:
				break;
			case BIKE_SESSION:	session = BikeSession::getInstance(paramArray[0].toFloat());
								session->setSessionActive();
								session->sendDataJson();
				break;
			default: Serial.print("ERROR: Not a valid Sessiontype");
				break;
		}
	}else{
		Serial.print("ERROR: There is already an active Session");
	}
}	

void SessionController::stopSession(){
	this->session->setSessionNotActive();
	Serial.print("{\"sessionId\":\"null\", \"status\":\"0\"}\n");
}

void SessionController::pauseSession(){

}

void SessionController::listenToEsp(){
	String message = "";
	while(Serial.available() > 0 && !message.endsWith("\n") || message == ""){
		message += Serial.readString();
	}
	parseJsonMessage(message);			
}

Session* SessionController::getSession(){
	return this->session;
}

void SessionController::parseJsonMessage(String jsonMsg){
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(jsonMsg);

	if(!root.success()){
		Serial.print("{\"status\":\"-2\"}\n");
		return;
	}
	sessionType type = (sessionType)root["sessionType"].as<int>();
	sessionCommand command = (sessionCommand)root["sessionCommand"].as<int>();
	JsonObject& params = root["params"];

	switch(command){
		case START_COMMAND: startSession(type, params); break;
		case PAUSE_COMMAND: pauseSession(); break;
		case STOP_COMMAND: stopSession(); break;
		default: Serial.print("{\"status\":\"-2\"}\n");break;
	}

}

String* SessionController::getParams(JsonObject& params){
	String* paramArray;
	JsonObject& data =  params;
	int index = 0;
	for (auto dataobj : data){
		paramArray[index] = dataobj.key;
		index++;
	}
	return paramArray;
}