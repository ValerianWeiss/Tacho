#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "Session.h"
#include "BikeSession.h"
#include "Constants.h"


class SessionController{
	private:  	
    static SessionController *sessionController;
    
    SessionController();
  protected:
     static Session *session;
  public:
    Session* getSession();
    static void listenToEsp();  
  	void stopSession();
  	void startSession(sessionType type);
    static SessionController* getInstance();
};

#endif
