#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "Session.h"
#include "BikeSession.h"
#include "Constants.h"
#include <ArduinoJson.h>

class SessionController{
	private:  	
    static SessionController *sessionController;
    
    SessionController();
    String* getParams(JsonArray& params);
    void parseJsonMessage(String jsonMsg);
    String* getParams(JsonObject& params);
 
  protected:
     static Session *session;
 
  public:
    Session* getSession();
    void listenToEsp();  
  	void stopSession();
  	void startSession(sessionType type, JsonObject& params);
    void pauseSession();
    static SessionController* getInstance();
};

#endif
