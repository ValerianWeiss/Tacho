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
	
		virtual void sendDatagram() = 0;		
		Session(unsigned int Id, unsigned long startTime);
	
	public:
    double getDuration();
		static bool active;
		virtual void calc() = 0;
    bool getSessionActive();
    void setSessionActive();
    void setSessionNotActive();
    int getId();
    void addDuration(double timeForOneSpin);
    Timer getTimer();
		
};

#endif
