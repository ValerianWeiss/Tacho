#ifndef BIKESESSION_H
#define BIKESESSION_H

#include <Arduino.h>
#include "Session.h"

class BikeSession : public Session{
  private:
  	float wheelHight;
  	float distance;
  	float currentSpeed;
  	float topSpeed;
  	float averageSpeed;  
	  static BikeSession *bikeSession;
	  BikeSession(unsigned int id, unsigned long startTime, float wheelHight); 

  protected:
  	void addDistance();
  	void calcSpeed(double timeForOneSpin);
  	void calcAvgSpeed();
    void addDuration(double timeForOneSpin);    
    void sendDatagram();
    
	
  public: 
    float getTopSpeed();
    float getWheelHight();
    float getDistance();
    float getCurrentSpeed();    
    float getAverageSpeed(); 
    void calc(); 
    void printToMonitor();
    void sendDataJson();    
    void startNewSession();
    Timer getTimer();
	  String print();
	  static BikeSession* getInstance(float wheelHight);
};

#endif
