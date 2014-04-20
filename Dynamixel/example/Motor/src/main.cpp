#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <dynamixel.h>
#include "motor.h"

using namespace std;

#define MOTOR_ID		1

int main(){

	bool b = 0;
	int deviceIndex = 0;
	int baudnum = 1;

	///////// Open USB2Dynamixel ////////////
	if( dxl_initialize(deviceIndex, baudnum) == 0 )
	{
		printf( "Failed to open USB2Dynamixel!\n" );
		printf( "Press Enter key to terminate...\n" );
		getchar();
		return 0;
	}
	else
		printf( "Succeed to open USB2Dynamixel!\n" );
	

	Motor motor1(MOTOR_ID, SERVOMODE);
	
	while(1)
	{
		printf( "Press Enter key to continue!(press ESC and Enter to quit)\n" );
		if(getchar() == 0x1b)
			break;

		if(b)
			motor1.setGoalPosition(1023);
		else
			motor1.setGoalPosition(0);

		b ^= 1;		//change b

	}

	
	
	// Close device
	dxl_terminate();
	return 0;
}

