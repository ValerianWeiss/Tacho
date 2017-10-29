#include "Timer.h"
#include "Constants.h"
#include <Arduino.h>

Timer::Timer(): prevMillis(millis()), prevEventMillis(millis()), rollovers(0){}

Timer::~Timer(){}

int Timer::overallRollovers = 0;

unsigned long Timer::checkForRollover(){
	if(this->prevMillis > millis()){
		this->rollovers++;
		this->overallRollovers++;
	}
	this->prevMillis = millis();
}

double Timer::calcDiff(){
	double result;
	if(this->rollovers > 0){
		result = (double)(MAX_MILLIS - this->prevEventMillis + (rollovers - 1) * MAX_MILLIS + millis());
	}else{    
    	result = (double)(millis() - this->prevEventMillis);
	}
	this->prevEventMillis = millis();
	this->rollovers = 0;
  	//result devided by 1000 to convert result in seconds
	return result/1000;
}



