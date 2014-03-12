#include "car.h"
#include <stdio.h>

void Car::setSpeed(int theSpeed, bool dir){
	
	switch(turn)
	{
	case NO_TURN:
		//set all wheels same speed
		frontLeftWheel.setSpeed(theSpeed, dir);
		backLeftWheel.setSpeed(theSpeed, dir);
		frontRightWheel.setSpeed(theSpeed, !dir);
		backRightWheel.setSpeed(theSpeed, !dir);	
		break;
	case LEFT_TURN:
		//set left wheels TURN_MAGNITUDE of right wheels
		frontLeftWheel.setSpeed(theSpeed*TURN_MAGNITUDE, dir);
		backLeftWheel.setSpeed(theSpeed*TURN_MAGNITUDE, dir);
		frontRightWheel.setSpeed(theSpeed, !dir);
		backRightWheel.setSpeed(theSpeed, !dir);
		break;
	case RIGHT_TURN:
		//set right wheels TURN_MAGNITUDE of left wheels
		frontLeftWheel.setSpeed(theSpeed, dir);
		backLeftWheel.setSpeed(theSpeed, dir);
		frontRightWheel.setSpeed(theSpeed*TURN_MAGNITUDE, !dir);
		backRightWheel.setSpeed(theSpeed*TURN_MAGNITUDE, !dir);
		break;
	}
	speed = theSpeed;
	direction = dir;
	
}

void Car::turnCar(int theTurn){
	turn = theTurn;
	setSpeed(speed, direction);
}



