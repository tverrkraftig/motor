#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <dynamixel.h>
#include <pthread.h>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include "car.h"
#include "manipulator.h"
#include "interface.h"
#include "json_processing.h"
#include "sensor.h"

using namespace std;

//put ID of the wheels here
#define FRONT_RIGHT_WHEEL	1
#define BACK_RIGHT_WHEEL	3
#define FRONT_LEFT_WHEEL	0
#define BACK_LEFT_WHEEL		2

#define MAN_ONE			4		//zero at 511
#define MAN_TWO			7		//zero at 511, not allowed to go under
#define MAN_THREE		5		//zero at 511

#define SENSOR			100

#define GRIPPER_LEFT		12
#define GRIPPER_RIGHT		6

void *sendSensorData(void *ptr);
void printError(int);

int main(){

	pthread_t thread1;
	int deviceIndex = 0;
	int baudnum = 1;
	string command;
	vector <string> commands;
	string strCheck = "position";
	
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
	
	//windowInit();
	Car car1(FRONT_RIGHT_WHEEL, FRONT_LEFT_WHEEL, BACK_RIGHT_WHEEL, BACK_LEFT_WHEEL);
	Manipulator manipulator1(MAN_ONE, MAN_TWO, MAN_THREE, GRIPPER_LEFT, GRIPPER_RIGHT);
	//Sensor sensor1(SENSOR);

	try{
		//sensor1.playMelody(6);
		//sleep(1);
		//manipulator1.goToPosition(0,0,155+77);
		//manipulator1.setGripper(0);
	}
	catch(MotorException e) {
		printf("ID: %d lost\n",e.ID);
		printError(e.status);
	}
	//get old commands from server and disregard them
	vector <string> dummy = json_get_commands(0);
	//pthread_create( &thread1, NULL, sendSensorData, &sensor1 );
	manipulator1.setGripper(1);
	manipulator1.drawLine(50,200,50,150,0);
	manipulator1.drawLine(50,175,25,175,0);
	manipulator1.drawLine(25,200,25,150,0);
		while(1)
		{
			try{
				//checkEvent(manipulator1, car1);

				
				
//				for(int i = 0; i < 130; i+=1)
//				{
//					manipulator1.goToPosition(0,150,i);
//					usleep(5000);
//				}
//				for(int i = 130; i > 0; i-=1)
//				{
//					manipulator1.goToPosition(0,150,i);
//					usleep(5000);
//				}
//				
//				for(int i = 0; i < 100; i+=10)
//				{
//					manipulator1.goToPosition(i,150,0);
//					usleep(50000);
//				}
//				for(int i = 100; i > -100; i-=10)
//				{
//					manipulator1.goToPosition(i,150,0);
//					usleep(50000);
//				}
//				for(int i = -100; i < 0; i+=10)
//				{
//					manipulator1.goToPosition(i,150,0);
//					usleep(50000);
//				}
				

//				while(commands.empty())
//				{
//					commands = json_get_commands(0);
//				}
//				while(!commands.empty())
//				{
//					command = commands.front();
//					commands.erase(commands.begin());
//					if(command == "forward")
//						car1.setSpeed(1023,1);
//						
//					else if(command == "backward")
//						car1.setSpeed(1023,0);
//						
//					else if(command == "stop")
//						car1.setSpeed(0,1);
//						
//					else if(command == "leftTurn")
//						car1.turnCar(LEFT_TURN);
//						
//					else if(command == "rightTurn")
//						car1.turnCar(RIGHT_TURN);
//						
//					else if(command == "noTurn")
//						car1.turnCar(NO_TURN);
//						
//					else if(command == "gripClose")
//						manipulator1.setGripper(1);
//						
//					else if(command == "gripOpen")
//						manipulator1.setGripper(0);
//						
//					else if(command.find(strCheck) != string::npos){
//						size_t found1 = command.find(" ");
//						size_t found2 = command.find(" ", found1+1);
//						size_t found3 = command.find(" ", found2+1);
//						string nr1 = command.substr(found1+1, found2-found1);
//						string nr2 = command.substr(found2+1, found3-found2);
//						string nr3 = command.substr(found3+1);

//						int x = atoi(nr1.c_str());
//						int y = atoi(nr2.c_str());
//						int z = atoi(nr3.c_str());
//						manipulator1.goToPosition(x, y, z);
//					}
//					
//					else
//						printf("Unknown command\n");

//					printf("command: %s\n", command.c_str());
//				}
			}

			catch(MotorException e) {
				printf("ID: %d lost\n",e.ID);
				printError(e.status);
			}
	
		}

	
	
	// Close device
	car1.setSpeed(0,1);
	dxl_terminate();
	return 0;
}

//thread function for continously sending data
void *sendSensorData(void *ptr){
	Sensor* p = (Sensor*)ptr;
	int data;
	map <string,double> sensorData;
	while(1){
		try{
		//get data and put it in the map
		data = p->getIR(CENTER);
		printf("\nIR center: %d\n",data);
		sensorData["IR center"] = data;
		
		data = p->getIR(LEFT);
		printf("IR left: %d\n",data);
		sensorData["IR left"] = data;

		data = p->getIR(RIGHT);
		printf("IR right: %d\n",data);
		sensorData["IR right"] = data;
		//send data
		json_send_data(sensorData);
		//clear map
		sensorData.clear();
		//sleep for 100ms
		usleep(100000);
		}
		
		catch(MotorException e) {
			printf("ID: %d lost\n",e.ID);
			printError(e.status);
		}
	}
}

void printError(int status){
	switch(status)
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
