#include <BikeSession.h>
#include <Constants.h>
#include <Session.h>
#include <SessionController.h>
#include <Timer.h>

//#include <ESP8266WiFi.h>

SessionController* sessionController;

void setup(){
	 Serial.begin(BAUD_RATE);
	 //Testing
	 sessionController = SessionController::getInstance();
	 sessionController->startSession(BIKE_SESSION);
}

void loop(){
  
  if(sessionController->session->getId() == BIKE_SESSION){
    sessionController->session->getTimer().checkForRollover();
    BikeSession *session = (BikeSession*)sessionController->session;
    if(session->active/* && if read(LOW)*/){
      session->calc();      
      //Test output
      session->printToMonitor();
    }
  }
  //Random spintimintervall
  int i = random(20,1000);
  Serial.print((double)i/1000,4);
  Serial.print("\n");
  delay(i);
}
	

