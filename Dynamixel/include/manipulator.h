#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_

#include "motor.h"

#define PI 3.14159265

class Manipulator{
public:	
	Manipulator(int IDOne ,int IDTwo,int IDThree, int IDGrip_left, int IDGrip_right ) : one(IDOne, SERVOMODE), two(IDTwo, SERVOMODE), three(IDThree, SERVOMODE), 
	grip_left(IDGrip_left, SERVOMODE), grip_right(IDGrip_right, SERVOMODE) {theta1 = 0; theta2 = 0; theta3 = 0;};
	void goToPosition(int, int, int);
	void setAngles(float, float, float);
	void setGripper(bool);
private:
	float theta1;
	float theta2;
	float theta3;
	Motor one;
	Motor two;
	Motor three;
	Motor grip_left;
	Motor grip_right;
};

#endif
