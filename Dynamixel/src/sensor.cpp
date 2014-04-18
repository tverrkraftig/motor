#include "motor.h"
#include "sensor.h"
#include "dynamixel.h"
#include "stdio.h"

Sensor::Sensor(int theID){
	ID = theID;
	commStatus = COMM_RXSUCCESS;
	mode = IDLE_MODE;
}

int Sensor::getLight(int pos){
		
	int data = dxl_read_byte( ID, LIGHT_LEFT_DATA + pos );
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
	{
		mode = FAILSAFE_MODE;
		printf("sensor lost\n");
	}	
	return data;
}

int Sensor::getIR(int pos){
		
	int data = dxl_read_byte( ID, IR_LEFT_FIRE_DATA + pos );
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
	{
		mode = FAILSAFE_MODE;
		printf("sensor lost\n");
	}
		
		
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
	{
		mode = FAILSAFE_MODE;
		printf("sensor lost\n");
	}
	dxl_write_byte(ID, BUZZER_DATA_NOTE, song);
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
	{
		mode = FAILSAFE_MODE;
		printf("sensor lost\n");
	}
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

