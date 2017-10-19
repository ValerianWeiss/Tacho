#include <BikeSession.h>
#include <Constants.h>
#include <Session.h>
#include <SessionController.h>
#include <Timer.h>

SessionController* sessionController;

void setup(){
	 Serial.begin(BAUD_RATE);
	 //Testing
	 sessionController = SessionController::getInstance();
	 sessionController->startSession(BIKE_SESSION);
}

void loop(){
  sessionController->listenToEsp();

  if(sessionController->getSession()->getSessionState() == true){  
    switch(sessionController->getSession()->getId()){
      case BIKE_SESSION:          
          sessionController->getSession()->getTimer().checkForRollover();
          sessionController->getSession()->calc();
          sessionController->getSession()->sendDataJson();
          break;
      
      default: //TODO implement a default case
          break;
    }
  }
 
  //Random spintimintervall
  int i = random(20,1000);
  Serial.print((double)i/1000,4);
  Serial.print("\n");
  delay(i);
}
	

