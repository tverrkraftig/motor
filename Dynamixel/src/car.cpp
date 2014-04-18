#include "car.h"
#include <stdio.h>

void Car::setSpeed(int theSpeed, bool dir){
	try{
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
	catch(MotorException e) {
		printf("ID: %d lost\n",e.ID);
		printError(e.status);
		setMode(FAILSAFE_MODE);
		printf("Wheels lost!\n");
	}
	
}

void Car::turnCar(int theTurn){
	try{
		bool direction;
		turn = theTurn;
		if(speed != 0){
			setSpeed(speed, direction);
			return;
		}
		if(turn == NO_TURN){
			setSpeed(0,1);
			return;
		}
		if(turn == LEFT_TURN)
			direction = 0;
		if(turn == RIGHT_TURN)
			direction = 1;

		printf("direction %d\n",direction);
		frontLeftWheel.setSpeed(1023*TURN_MAGNITUDE, direction);
		backLeftWheel.setSpeed(1023*TURN_MAGNITUDE, direction);
		frontRightWheel.setSpeed(1023*TURN_MAGNITUDE, direction);
		backRightWheel.setSpeed(1023*TURN_MAGNITUDE, direction);
	}
	catch(MotorException e) {
		printf("ID: %d lost\n",e.ID);
		printError(e.status);
		setMode(FAILSAFE_MODE);
		printf("Wheels lost!\n");
	}
	
}

void Car::setMode(int theMode){
	mode = theMode;
}

int Car::getMode(){
	return mode;
}

void Car::ping(){
	int count = 0;
	
	count += frontLeftWheel.ping();
	count += backLeftWheel.ping();
	count += frontRightWheel.ping();
	count += backRightWheel.ping();

	if(count == 4){
		printf("All wheels active!\n");
		setMode(IDLE_MODE);
	}
	else{
		setMode(FAILSAFE_MODE);
	}
}



