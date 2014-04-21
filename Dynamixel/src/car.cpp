#include "car.h"
#include <stdio.h>

void Car::setSpeed(int theSpeed, bool dir){
	try{
		switch(turn)
		{
		case NO_TURN:
			//set all wheels same speed
			frontLeftWheel.setSpeed(theSpeed, !dir);
			backLeftWheel.setSpeed(theSpeed, !dir);
			frontRightWheel.setSpeed(theSpeed, dir);
			backRightWheel.setSpeed(theSpeed, dir);	
			break;
		case LEFT_TURN:
			//set left wheels TURN_MAGNITUDE of right wheels
			frontLeftWheel.setSpeed(theSpeed*TURN_MAGNITUDE, !dir);
			backLeftWheel.setSpeed(theSpeed*TURN_MAGNITUDE, !dir);
			frontRightWheel.setSpeed(theSpeed, dir);
			backRightWheel.setSpeed(theSpeed, dir);
			break;
		case RIGHT_TURN:
			//set right wheels TURN_MAGNITUDE of left wheels
			frontLeftWheel.setSpeed(theSpeed, !dir);
			backLeftWheel.setSpeed(theSpeed, !dir);
			frontRightWheel.setSpeed(theSpeed*TURN_MAGNITUDE, dir);
			backRightWheel.setSpeed(theSpeed*TURN_MAGNITUDE, dir);
			break;
		}
		speed = theSpeed;
		direction = dir;
	}
	catch(MotorException e) {
		printf("ID: %d lost\n",e.ID);
		printError(e.status);
		if(mode == IDLE_MODE)
		{
			mode = FAILSAFE_MODE;
			printf("Wheels lost!\n");
			startPing();
		}
	}
	
}

void Car::turnCar(int theTurn){
	try{
		turn = theTurn;
		if(speed != 0){
			setSpeed(speed, direction);
			return;
		}
		if(turn == NO_TURN){
			setSpeed(0,1);
			return;
		}
		bool dir;
		if(turn == LEFT_TURN)
			dir = 1;
		if(turn == RIGHT_TURN)
			dir = 0;

		printf("direction %d\n",direction);
		frontLeftWheel.setSpeed(1023*TURN_MAGNITUDE, dir);
		backLeftWheel.setSpeed(1023*TURN_MAGNITUDE, dir);
		frontRightWheel.setSpeed(1023*TURN_MAGNITUDE, dir);
		backRightWheel.setSpeed(1023*TURN_MAGNITUDE, dir);
	}
	catch(MotorException e) {
		printf("ID: %d lost\n",e.ID);
		printError(e.status);
		if(mode == IDLE_MODE)
		{
			mode = FAILSAFE_MODE;
			printf("Wheels lost!\n");
			startPing();
		}
	}
	
}

void Car::setMode(int theMode){
	mode = theMode;
}

int Car::getMode(){
	return mode;
}

void Car::ping(){
	printf("Ping Car\n");
	while(1){
		int count = 0;
	
		count += frontLeftWheel.ping();
		count += backLeftWheel.ping();
		count += frontRightWheel.ping();
		count += backRightWheel.ping();
		
		if(count == 4){
			printf("All wheels active!\n");
			setMode(IDLE_MODE);
			return;
		}
	}
}

void Car::startPing(){
	pthread_create(&thread, NULL, Car::staticEntryPoint, this);
}

void * Car::staticEntryPoint(void * c)
{
    ((Car *) c)->ping();
    return NULL;
}



