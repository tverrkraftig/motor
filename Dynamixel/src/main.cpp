#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <dynamixel.h>
#include <pthread.h>
#include <vector>
#include <string>
#include "car.h"
#include "manipulator.h"
#include "interface.h"

using namespace std;

//put ID of the wheels here
#define FRONT_RIGHT_WHEEL	1
#define BACK_RIGHT_WHEEL	3
#define FRONT_LEFT_WHEEL	0
#define BACK_LEFT_WHEEL		2

#define MAN_ONE			4		//zero at 511
#define MAN_TWO			7		//zero at 511, not allowed to go under
#define MAN_THREE		5		//zero at 511
#define MAN_FOUR		6		//zero at 511

//void *communicationWithServer(void *ptr);


int main(){

	pthread_t thread1;
	int deviceIndex = 0;
	int baudnum = 1;
	string command;
	vector <string> commands;
	
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

	windowInit();
	
	Car car1(FRONT_RIGHT_WHEEL, FRONT_LEFT_WHEEL, BACK_RIGHT_WHEEL, BACK_LEFT_WHEEL);
	Manipulator manipulator1(MAN_ONE, MAN_TWO, MAN_THREE, MAN_FOUR);
	
	
	//pthread_create( &thread1, NULL, interface, (void*) car1 );
	
		while(1)
		{
			try{

				checkEvent(manipulator1);
				
//				for(int i = 0; i < 130; i+=10)
//				{
//					manipulator1.goToPosition(0,100,i);
//					usleep(50000);
//				}
//				for(int i = 130; i > 0; i-=10)
//				{
//					manipulator1.goToPosition(0,100,i);
//					usleep(50000);
//				}
//				
//				for(int i = 0; i < 100; i+=10)
//				{
//					manipulator1.goToPosition(i,100,0);
//					usleep(50000);
//				}
//				for(int i = 100; i > -100; i-=10)
//				{
//					manipulator1.goToPosition(i,100,0);
//					usleep(50000);
//				}
//				for(int i = -100; i < 0; i+=10)
//				{
//					manipulator1.goToPosition(i,100,0);
//					usleep(50000);
//				}

				
//				while(commands.empty())
//				{
////					commands = getCommands();
//				}
//				while(!commands.empty())
//				{
//					command = commands.front();
//					commands.erase(commands.begin());
//					if(command == "forward")
//						car1.setSpeed(1023,1);
//					if(command == "backward")
//						car1.setSpeed(1023,0);
//					if(command == "stop")
//						car1.setSpeed(0,1);
//					if(command == "leftTurn")
//						car1.turnCar(LEFT_TURN);
//					if(command == "rightTurn")
//						car1.turnCar(RIGHT_TURN);
//					if(command == "noTurn")
//						car1.turnCar(NO_TURN);
//					
//					printf("command: %s\n", command.c_str());
//				}
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
	car1.setSpeed(0,1);
	dxl_terminate();
	printf( "Press Enter key to terminate...\n" );
	getchar();
	
	return 0;
}

//void *communicationWithServer(void *ptr){
//	while(1){
//		//get and send with server here
//	}
//}
