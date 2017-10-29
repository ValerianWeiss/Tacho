#include "Session.h"

bool Session::active = false;

Session::Session(unsigned int Id, unsigned long startTime) : sessionId (Id), startTime(startTime), duration(0.0){
  this->timer = new Timer();
}

Session::~Session(){
  delete timer;
}

bool Session::getSessionState(){
	return this->active;
}

void Session::setSessionActive(){
	this->active = true;
}

void Session::setSessionNotActive(){
	this->active = false;
}

double Session::getDuration(){
  return this->duration;
}

int Session::getId(){
  return this->sessionId;
}

void Session::addDuration(double timeForOneSpin){
  this->duration += timeForOneSpin;
}
Timer Session::getTimer(){
  return *timer;
}

