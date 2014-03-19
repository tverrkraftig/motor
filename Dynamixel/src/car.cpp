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
		//turn if speed is 0
		if(theSpeed == 0){
			frontLeftWheel.setSpeed(10*TURN_MAGNITUDE, !dir);
			backLeftWheel.setSpeed(10*TURN_MAGNITUDE, !dir);
			frontRightWheel.setSpeed(10*TURN_MAGNITUDE, !dir);
			backRightWheel.setSpeed(10*TURN_MAGNITUDE, !dir);	
		}
		//set left wheels TURN_MAGNITUDE of right wheels
		frontLeftWheel.setSpeed(theSpeed*TURN_MAGNITUDE, dir);
		backLeftWheel.setSpeed(theSpeed*TURN_MAGNITUDE, dir);
		frontRightWheel.setSpeed(theSpeed, !dir);
		backRightWheel.setSpeed(theSpeed, !dir);
		break;
	case RIGHT_TURN:
		//turn if speed is 0
		if(theSpeed == 0){
			frontLeftWheel.setSpeed(10*TURN_MAGNITUDE, dir);
			backLeftWheel.setSpeed(10*TURN_MAGNITUDE, dir);
			frontRightWheel.setSpeed(10*TURN_MAGNITUDE, dir);
			backRightWheel.setSpeed(10*TURN_MAGNITUDE, dir);	
		}
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

void Car::setMode(int theMode){
	if(mode == FRONT_OFF_MODE && theMode == BACK_OFF_MODE){
		mode = ALL_OFF_MODE;
		return;
	}
		
	if(mode == BACK_OFF_MODE && theMode == FRONT_OFF_MODE){
		mode = ALL_OFF_MODE;
		return;
	}
	mode = theMode;
}

int Car::getMode(){
	return mode;
}



