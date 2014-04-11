#include "motor.h"
#include "sensor.h"
#include "dynamixel.h"
#include "stdio.h"

Sensor::Sensor(int theID){
	ID = theID;
	commStatus = COMM_RXSUCCESS;
}

int Sensor::getSound(){
	return 1;
}

int Sensor::getLight(int pos){
	return 1;
}

int Sensor::getIR(int pos){
	return 1;
}
