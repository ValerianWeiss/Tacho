#include "BikeSession.h"
#include "Timer.h"
#include "Constants.h"
#include "SessionController.h"
#include "Session.h"


BikeSession* BikeSession::bikeSession = NULL;

BikeSession* BikeSession::getInstance(float wheelHight){
	if(bikeSession == NULL){
		//TODO: think about the time that shoud be but in here -> maybe timestamp from device
		bikeSession = new BikeSession(BIKE_SESSION, millis(), wheelHight);
	}
	return bikeSession;
}

BikeSession::BikeSession(unsigned int id, unsigned long startTime, float wheelHight) : Session(id, startTime){
	this->wheelHight = wheelHight;
  this->distance = 0.0;
  this->currentSpeed = 0.0;
  this->topSpeed = 0.0;
  this->averageSpeed = 0.0;
}

void BikeSession::addDistance(){
	this->distance += Pi*this->wheelHight;
}

void BikeSession::calcSpeed(double timeForOneSpin){
	//Expected timeForOneSpin in seconds time unit
	//Calc speed to format km/h 
	this->currentSpeed = (float)this->wheelHight*Pi/timeForOneSpin*3.6;
	if(this->topSpeed < this->currentSpeed){
		this->topSpeed = this->currentSpeed;
	}
}

void BikeSession::calc(){
	//Expected timeForOneSpin in milliseconds time unit
	double timeForOneSpin = this->timer.calcDiff();

	//For Testing
	Serial.print("timeForOneSpin: ");
	Serial.print(timeForOneSpin);
	Serial.print("\n");
	
	
  Session::addDuration(timeForOneSpin);
  if(timeForOneSpin > 0){
    addDistance();
    calcSpeed(timeForOneSpin); 
    calcAvgSpeed();
  }
}

void BikeSession::sendDatagram(){
	//TODO: datagram.send();
}

void BikeSession::calcAvgSpeed(){
	//Expected distance in unit "m" and totalTime in Seconds
	this->averageSpeed = (this->distance/this->duration)*3.6;
}

Timer BikeSession::getTimer(){
  return timer;
}

void BikeSession::startNewSession(){
  //Add to Session Array or make session active
}

float BikeSession::getTopSpeed(){
  return topSpeed;
}

float BikeSession::getWheelHight(){
  return wheelHight;
}

float BikeSession::getDistance(){
  return distance;
}
float BikeSession::getCurrentSpeed(){
  return currentSpeed;    
}

float BikeSession::getAverageSpeed(){
  return averageSpeed;  
}

void BikeSession::printToMonitor(){
    Serial.print("Duration: ");
    Serial.print(getDuration(),4);
    Serial.print("\n");
    Serial.print("Distance: ");
    Serial.print(getDistance(),4);
    Serial.print("\n");
    Serial.print("Current Speed: ");
    Serial.print(getCurrentSpeed(),4);
    Serial.print("\n");
    Serial.print("TopSpeed: ");
    Serial.print(getTopSpeed(),4);
    Serial.print("\n");
    Serial.print("Average Speed: ");
    Serial.print(getAverageSpeed(),4);
    Serial.print("\n\n");
}



