#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "Session.h"
#include "BikeSession.h"
#include "Constants.h"
#include <ArduinoJson.h>

class SessionController{
	private:  	
    static SessionController *sessionController;
    static String messageBuffer;
    
    SessionController();
    void getParamsFromJson(float* paramArray, JsonArray& params);
    void parseJsonMessage(String jsonMsg);
    String getJsonMessage(String jsonMsg);
 
  protected:
     static Session *session;
 
  public:
    Session* getSession();
    void listenToEsp();  
  	void stopSession();
  	void startSession(sessionType type, JsonArray& params);
    void pauseSession();
    static SessionController* getInstance();
};

#endif
