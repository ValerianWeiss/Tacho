#include <BikeSession.h>
#include <Constants.h>
#include <Session.h>
#include <SessionController.h>
#include <Timer.h>

SessionController* sessionController;

void setup(){
	 Serial.begin(BAUD_RATE);
	 sessionController = SessionController::getInstance();
}

void loop(){
  sessionController->listenToEsp();

  if(sessionController->getSession() != NULL
        && sessionController->getSession()->getSessionState()){  
          
    switch(sessionController->getSession()->getId()){
      case BIKE_SESSION:   
          sessionController->getSession()->getTimer().checkForRollover();
          sessionController->getSession()->calc();
          sessionController->getSession()->sendDataJson();
          break;
      
      default: //Not to be handeld -> you cant start a session with an
               //invalid SessionId
          break;
    }
  }
  
  //Debugging function -> just use if you want to see the data of the Session
  //sessionController->getSession()->printToMonitor();
  //Random spintimeintervall
  int i = random(20,1000);
  delay(i);
}
	

