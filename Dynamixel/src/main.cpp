#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <dynamixel.h>
#include "car.h"


int main(){

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

	
	Car car1;
	//sleep(1);
	
	try{
	
		while(1)
		{
				printf( "Press Enter key to continue!(press ESC and Enter to quit)\n" );
				if(getchar() == 0x1b)
					break;

				car1.turnCar(NO_TURN);
				car1.setSpeed(1023, 0);
				sleep(1);
				car1.turnCar(LEFT_TURN);
				sleep(1);
				car1.turnCar(RIGHT_TURN);
				sleep(1);
				car1.turnCar(NO_TURN);
				car1.setSpeed(1023,1);
				sleep(1);
				car1.setSpeed(0,0);
			
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
	car1.setSpeed(0,false);
	dxl_terminate();
	printf( "Press Enter key to terminate...\n" );
	getchar();
	
	return 0;
}
