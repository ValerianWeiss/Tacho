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
void SessionController::startSession(sessionType type, JsonArray& params){
	if(!this->session->getSessionState()){
		String* params = getParams();			
		switch(type){
			case SESSION:
				break;
			case BIKE_SESSION: 	session = BikeSession::getInstance(params[0].toFloat());
								session->setSessionActive();
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
}

void SessionController::pauseSession(){

}

void SessionController::listenToEsp(){
	String message = "";
	while(Serial.available() > 0){
		message += Serial.read();
	}			
}

Session* SessionController::getSession(){
	return this->session;
}

void SessionController::parseJsonMessage(String jsonMsg){
	
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(jsonMsg);

	if(!root.success()){
		return;
	}

	sessionType type = root["sessionType"];
	sessionCommand command = root["sessionCommand"];
	JsonArray& params = root["params"];

	switch(command){
		case START_COMMAND: startSession(type, params); break;
		case PAUSE_COMMAND: pauseSession(); break;
		case STOP_COMMAND: stopSession(); break;
		default:break;
	}

}

String* SessionController::getParams(JsonArray& params){
	String* paramArray;
	JsonObject& data =  params["data"];
	int index = 0;
	for (auto dataobj : data){
		paramArray[index] = dataobj.value.asString();
	}
	return paramArray;
}