#include "motor.h"
#include "sensor.h"
#include "dynamixel.h"
#include "stdio.h"

Sensor::Sensor(int theID){
	ID = theID;
	commStatus = COMM_RXSUCCESS;
	mode = IDLE_MODE;
}

int Sensor::getSound(){
	return 1;
}

int Sensor::getLight(int pos){
	//if sensor unreachable
	if(commStatus != COMM_RXSUCCESS)
		return -1;
		
	int data = dxl_read_byte( ID, LIGHT_LEFT_DATA + pos );
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
		throw MotorException(ID,commStatus);
		
	return data;
}

int Sensor::getIR(int pos){
		
	int data = dxl_read_byte( ID, IR_LEFT_FIRE_DATA + pos );
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
		throw MotorException(ID,commStatus);
		
	return data;
}

void Sensor::playMelody(int song){

	if(song < 0 || song > 26){
		printf("invalid input\n");
		return;
	}
	dxl_write_byte(ID, BUZZER_DATA_TIME, 255);
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
		throw MotorException(ID,commStatus);
	
	dxl_write_byte(ID, BUZZER_DATA_NOTE, song);
	commStatus = dxl_get_result();
//	if(commStatus != COMM_RXSUCCESS)
//		throw MotorException(ID,commStatus);
}

void Sensor::ping(){
	dxl_ping(ID);
	commStatus = dxl_get_result();
	if( commStatus == COMM_RXSUCCESS )
	{
		printf("Sensor ID: %d active!\n",ID);
		setMode(IDLE_MODE);
	}
	else{
		setMode(FAILSAFE_MODE);
	}
}

void Sensor::setMode(int theMode){
	mode = theMode;
}

int Sensor::getMode(){
	return mode;
}

