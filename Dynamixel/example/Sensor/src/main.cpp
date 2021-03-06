#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <dynamixel.h>
#include "sensor.h"
#include "songs.h"
#include "motor.h"


using namespace std;

//put ID of sensor here
#define SENSOR		100

int main(){

	int deviceIndex = 0;
	int baudnum = 1;

	printf("-------Sensor TEST PROGRAM-------\n");

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


	Sensor sensor1(SENSOR);
	sensor1.playMelody(FurElise,sizeof(FurElise));
	
	while(1)
	{
		data = sensor1.getIR(CENTER);
		printf("\nIR center: %d\n",data);
		
		data = sensor1.getIR(LEFT);
		printf("IR left: %d\n",data);

		data = sensor.getIR(RIGHT);
		printf("IR right: %d\n",data);

		printf("\n");
		usleep(100000);
	}

	// Close device
	dxl_terminate();
	return 0;
}

