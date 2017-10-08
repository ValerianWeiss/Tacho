#ifndef TACHODATAGRAMM_H
#define TACHODATAGRAMM_H

class TachoDatagramm{
	public:
		float distance;
		float currentSpeed;
		float topSpeed;
		float averageSpeed;
		float maxSpeed;
		
		TachoDatagramm(float distance, float currentSpeed, float topSpeed, float averageSpeed, float maxSpeed, unsigned) 
									: distance(distance), currentSpeed(currentSpeed), averageSpeed(averageSpeed), maxSpeed(maxSpeed), Datagramm()
		
};
#endif