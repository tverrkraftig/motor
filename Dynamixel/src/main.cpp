#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <dynamixel.h>
#include <pthread.h>
#include <vector>
#include "car.h"

using namespace std;

//put ID of the wheels here
#define FRONT_RIGHT_WHEEL	1
#define BACK_RIGHT_WHEEL	3
#define FRONT_LEFT_WHEEL	0
#define BACK_LEFT_WHEEL		2

void *communicationWithServer(void *ptr);


int main(){

	pthread_t thread1;
	int threadinput;
	int deviceIndex = 0;
	int baudnum = 1;

	pthread_create( &thread1, NULL, communicationWithServer, (void*) threadinput );
	
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

	Car car1(FRONT_RIGHT_WHEEL, FRONT_LEFT_WHEEL, BACK_RIGHT_WHEEL, BACK_LEFT_WHEEL);
	//sleep(1);

	
		while(1)
		{
			try{
				printf( "Press Enter key to continue!(press ESC and Enter to quit)\n" );
				if(getchar() == 0x1b)
					break;

				car1.turnCar(NO_TURN);
				car1.setSpeed(500, 0);
				sleep(1);
				car1.setSpeed(0,0);
				/*car1.turnCar(LEFT_TURN);
				sleep(1);
				car1.turnCar(RIGHT_TURN);
				sleep(1);
				car1.turnCar(NO_TURN);
				car1.setSpeed(1023,1);
				sleep(1);	
				car1.setSpeed(0,0);*/
			}

			catch(MotorException e) {

				printf("ID: %d lost\n",e.ID);

				switch(e.status)
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
	
		}

	
	
	// Close device
	car1.setSpeed(0,false);
	dxl_terminate();
	printf( "Press Enter key to terminate...\n" );
	getchar();
	
	return 0;
}

void *communicationWithServer(void *ptr){
	while(1){
		//get and send with server here
	}
}
