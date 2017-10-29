#include "SessionController.h"
#include "BikeSession.h"
#include "Session.h"
#include "Constants.h"
#include "GlobalFunctions.h"
#include <ArduinoJson.h>

SessionController* SessionController::sessionController = NULL;
Session* SessionController::session = NULL;
String SessionController::messageBuffer = "";

SessionController::SessionController(){
}


SessionController * SessionController::getInstance(){
  if(sessionController == NULL){
    sessionController = new SessionController();
  }
  return sessionController;
}

//This func should be called by the listenToSignal function
//TODO Add args [] for differet Session types (e.g wheel hight for BikeSession)
void SessionController::startSession(sessionType type, JsonArray& params){
	float paramArray [params.size()];
	getParamsFromJson(paramArray, params);
	switch(type){

		case BIKE_SESSION:	
			if(!this->session->getSessionState()){
				session = BikeSession::getInstance(paramArray[0]);
				session->setSessionActive();
				session->sendDataJson();
			}							
			break;

		default: Serial.print("{\"status\":\"-5\"}");
			break;
	}	
}	

void SessionController::stopSession(){
	this->session->setSessionNotActive();
}

//To be implemented
void SessionController::pauseSession(){

}

//To Debug you can use this example message -> outcome should be a responese
//string with the current information about the session
//String* message 
//*message = "{\"sessionType\":\"1\",\"sessionCommand\":\"0\", \"params\":[\"0.6\"]}\n";
void SessionController::listenToEsp(){
	//This function is reading new Strings out of the Serial and 
	//wirtes it into the messageBuffer
	GlobalFunctions::readJsonFromSerial(&messageBuffer);
	String toSend = GlobalFunctions::getJsonMessage(messageBuffer);

	if(toSend != ""){
		parseJsonMessage(toSend);
		messageBuffer = messageBuffer.substring(messageBuffer.indexOf('}') + 1);	
	}
}

Session* SessionController::getSession(){
	return this->session;
}

void SessionController::parseJsonMessage(String jsonMsg){
	StaticJsonBuffer<500> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(jsonMsg);

	if(!root.success()){
		//an invalid json string has to be handeld -> send a response to the client		
		return;
	}	

	sessionType type = (sessionType)root["sessionType"].as<int>();
	sessionCommand command = (sessionCommand)root["sessionCommand"].as<int>();
	JsonArray& params = root["params"];

	switch(command){
		case START_COMMAND: startSession(type, params); break;
		case PAUSE_COMMAND: pauseSession(); break;
		case STOP_COMMAND: stopSession(); break;
		default: Serial.print("{\"status\":\"-4\"}");break;
	}

}

void SessionController::getParamsFromJson(float* paramArray, JsonArray& params){
	for(int i = 0; i < params.size(); i++){
		paramArray[i] = params.get<float>(i);
	}
}