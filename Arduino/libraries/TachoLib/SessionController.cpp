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
		float paramArray [params.size()];
		getParams(paramArray, params);
		switch(type){
			case SESSION:
				break;
			case BIKE_SESSION:	session = BikeSession::getInstance(paramArray[0]);
								session->setSessionActive();
								session->sendDataJson();
				break;
			default: Serial.print("{\"status\":\"-5\"}\n");
				break;
		}
	}else{
		Serial.print("{\"status\":\"-6\"}\n");
	}
}	

void SessionController::stopSession(){
	this->session->setSessionNotActive();
	Serial.print("{\"sessionId\":\"null\", \"status\":\"0\"}\n");
}

void SessionController::pauseSession(){

}

void SessionController::listenToEsp(){
	//To Debug you can use this example message -> outcome should be a responese
	//string with the current information about the session
	//String message = "{\"sessionType\":\"1\",\"sessionCommand\":\"0\", \"params\":[\"0.6\"]}\n";
	String message = "";
	long timer = millis();
	if(Serial.available() > 0){
		while(!message.endsWith("}\n")){
			message += Serial.readString();
		}
	}
	if(message != "" && message.endsWith("}\n")){
		parseJsonMessage(message);	
	}
}

Session* SessionController::getSession(){
	return this->session;
}

void SessionController::parseJsonMessage(String jsonMsg){
	StaticJsonBuffer<500> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(jsonMsg);

	if(!root.success()){
		Serial.print("{\"status\":\"-2\"}\n");
		return;
	}

	sessionType type = (sessionType)root["sessionType"].as<int>();
	sessionCommand command = (sessionCommand)root["sessionCommand"].as<int>();
	JsonArray& params = root["params"];

	switch(command){
		case START_COMMAND: startSession(type, params); break;
		case PAUSE_COMMAND: pauseSession(); break;
		case STOP_COMMAND: stopSession(); break;
		default: Serial.print("{\"status\":\"-4\"}\n");break;
	}

}

void SessionController::getParams(float* paramArray, JsonArray& params){
	for(int i = 0; i < params.size(); i++){
		paramArray[i] = params.get<float>(i);
	}
}