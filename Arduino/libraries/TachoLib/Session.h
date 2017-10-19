#ifndef SESSION_H
#define SESSION_H

#include <Arduino.h>
#include "Timer.h"

class Session{
	protected:
		unsigned int sessionId;
		double duration;
		unsigned long startTime;
		unsigned long endTime;	
    Timer timer;	
		static bool active;
	
		virtual void sendDatagram() = 0;		
		Session(unsigned int Id, unsigned long startTime);
	
	public:
    double getDuration();	
		virtual void calc() = 0;
		virtual void sendDataJson() = 0;
    bool getSessionState();
    void setSessionActive();
    void setSessionNotActive();
    int getId();
    void addDuration(double timeForOneSpin);
    Timer getTimer();
		
};

#endif
