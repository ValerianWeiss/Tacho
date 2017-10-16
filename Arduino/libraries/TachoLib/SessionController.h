#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "Session.h"
#include "BikeSession.h"
#include "Constants.h"


class SessionController{
	private:  	
    static SessionController *sessionController;
    
    SessionController();
    
  public:
    static Session *session;
    
    static void readFromESP();    
  	void listenToSignal();
  	void stopSession();
  	void startSession(sessionType type);
    static SessionController* getInstance();
};


#endif
