#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_

#include "motor.h"

#define PI 3.14159265

#define IDLE_MODE	0
#define FAILSAFE_MODE	1

class Manipulator{
public:	
	Manipulator(int IDOne ,int IDTwo,int IDThree, int IDGrip_left, int IDGrip_right ) : one(IDOne, SERVOMODE), two(IDTwo, SERVOMODE), three(IDThree, SERVOMODE), 
	grip_left(IDGrip_left, SERVOMODE), grip_right(IDGrip_right, SERVOMODE) {theta1 = 0; theta2 = 0; theta3 = 0; mode = IDLE_MODE;};
	void goToPosition(int, int, int);
	void setAngles(float, float, float);
	void setGripper(bool);
	void drawLine(int, int, int, int, int);
	void drawCircle(int, int, int, int, float, float);
	void setMode(int);
	int getMode();
	void ping();
private:
	float theta1;
	float theta2;
	float theta3;
	int mode;
	Motor one;
	Motor two;
	Motor three;
	Motor grip_left;
	Motor grip_right;
};

#endif
