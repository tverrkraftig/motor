#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <dynamixel.h>
#include "motor.h"


int main(){

	int deviceIndex = 0;
	int baudnum = 1;
	int GoalPos[2] = {0, 1023};
	int index = 0;
	
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

	sleep(1);
	
	Motor motor1(1, WHEELMODE);
	Motor motor2(2, WHEELMODE);
	Motor motor3(3, WHEELMODE);
	Motor motor4(0, WHEELMODE);
	
	try{
	
		while(1)
		{
				printf( "Press Enter key to continue!(press ESC and Enter to quit)\n" );
				if(getchar() == 0x1b)
					break;

				//Write goal position
				//motor1.setGoalPosition(GoalPos[index]);
				//index ^= 1;
				motor1.checkStatus();
				motor2.checkStatus();
				motor3.checkStatus();
				motor4.checkStatus();
				//pingTest();
			
		}
	}

	catch(int CommStatus) {
		switch(CommStatus)
		{
		case COMM_TXFAIL:
			printf("COMM_TXFAIL: Failed transmit instruction packet!\n");
			break;

		case COMM_TXERROR:
			printf("COMM_TXERROR: Incorrect instruction packet!\n");
			break;

		case COMM_RXFAIL:
			printf("COMM_RXFAIL: Failed get status packet from device!\n");
			break;

		case COMM_RXWAITING:
			printf("COMM_RXWAITING: Now recieving status packet!\n");
			break;

		case COMM_RXTIMEOUT:
			printf("COMM_RXTIMEOUT: There is no status packet!\n");
			break;

		case COMM_RXCORRUPT:
			printf("COMM_RXCORRUPT: Incorrect status packet!\n");
			break;

		default:
			printf("This is unknown error code!\n");
			break;
		}
	}
	
	// Close device
	motor1.setSpeed(0,1);
	motor2.setSpeed(0,1);
	motor3.setSpeed(0,1);
	motor4.setSpeed(0,1);
	dxl_terminate();
	printf( "Press Enter key to terminate...\n" );
	getchar();
	
	return 0;
}
