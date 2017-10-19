#include "SessionController.h"
#include "BikeSession.h"
#include "Session.h"
#include "Constants.h"

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
void SessionController::startSession(sessionType type){
	if(!this->session->getSessionState()){			
		switch(type){
			case SESSION:
				break;
			case BIKE_SESSION: 	session = BikeSession::getInstance(0.6); //added 0.6 for testing
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

void SessionController::listenToEsp(){
	String message = "";
	while(Serial.available() > 0){
		message += Serial.read();
	}
	Serial.println("Recieved: " + message); 			
}

Session* SessionController::getSession(){
	return this->session;
}