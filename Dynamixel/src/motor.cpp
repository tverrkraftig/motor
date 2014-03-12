#include "motor.h"
#include "dynamixel.h"
#include "stdio.h"

Motor::Motor(int theID, int theMode){
	ID = theID;
	mode = theMode;
	setMode(mode);
	//dxl_write_word( ID, MAX_TORQUE_L, 1023 );
	/*commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
		throw commStatus;
	printErrorCode();*/
}

int Motor::getMode(){
	return mode;
}

int Motor::getPosition(){
	int temp = dxl_read_word( ID, PRESENT_POSITION_L );
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
		throw commStatus;
	printErrorCode();
	position = temp;
	return position;
}

int Motor::getSpeed(){
	unsigned short temp = dxl_read_word( ID, PRESENT_SPEED_L );
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
		throw commStatus;
	printErrorCode();
	speed = temp & 1023;
	return speed;
}

void Motor::setGoalPosition(int thePosition){
	dxl_write_word( ID, GOAL_POSITION_L, thePosition );
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
		throw commStatus;
	printErrorCode();
}


void Motor::setMode(int theMode){
	
	switch(theMode)
	{
	case WHEELMODE:
		dxl_write_word( ID, CW_ANGLE_LIMIT_L, 0 );
		dxl_write_word( ID, CCW_ANGLE_LIMIT_L, 0 );
		/*commStatus = dxl_get_result();
		if(commStatus != COMM_RXSUCCESS)
			throw commStatus;
		printErrorCode();*/
		break;
	case SERVOMODE:
		dxl_write_word( ID, CW_ANGLE_LIMIT_L, 0 );
		dxl_write_word( ID, CCW_ANGLE_LIMIT_L, 1023 );
		/*commStatus = dxl_get_result();
		if(commStatus != COMM_RXSUCCESS)
			throw commStatus;
		printErrorCode();*/
		break;
	default:
		printf("unknown mode: %d\n", theMode);
		return;
	}
	mode = theMode;
}

void Motor::setSpeed(int theSpeed, bool theDirection){
	dxl_write_word( ID, MOVING_SPEED_L, theSpeed | (theDirection<<10) );
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
		throw commStatus;
	printErrorCode();
}

void Motor::setRotateDirection(int direction){
	
	switch(direction)
	{
	case CW:
		dxl_write_word(ID, MOVING_SPEED_L, 1024);
		break;
	case CCW:
		dxl_write_word(ID, MOVING_SPEED_L, 0);
		break;
	default:
		printf("invalid input: %d\n", direction);
		return;
	}
	commStatus = dxl_get_result();
	if(commStatus != COMM_RXSUCCESS)
		throw commStatus;
	printErrorCode();
	
	rotateDirection = direction;
}

// Print error bit of status packet
void Motor::printErrorCode()
{
	if(dxl_get_rxpacket_error(ERRBIT_VOLTAGE) == 1)
		printf("Input voltage error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_ANGLE) == 1)
		printf("Angle limit error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_OVERHEAT) == 1)
		printf("Overheat error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_RANGE) == 1)
		printf("Out of range error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_CHECKSUM) == 1)
		printf("Checksum error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_OVERLOAD) == 1)
		printf("Overload error!\n");

	if(dxl_get_rxpacket_error(ERRBIT_INSTRUCTION) == 1)
		printf("Instruction code error!\n");
}

void Motor::checkStatus()
{
	unsigned char temp;
	for(int i = 0; i<50; i++)
	{
		if(i == 10 || i == 45)
			continue;
		temp = dxl_read_byte( ID, i );
		printf("%d:\t%d\t%d\n", ID, i, temp);
	}
	printf("\n");
}

void pingTest(){
	for(int i = 0; i<254; i++){
		dxl_ping(i);
		if( dxl_get_result( ) == COMM_RXSUCCESS )
		{
			printf("ID: %d active!\n",i);
		}
	}
}


