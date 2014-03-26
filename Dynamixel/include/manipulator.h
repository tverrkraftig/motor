#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_

#include "motor.h"

#define D2	77	//length of first arm in mm
#define D3	94	//length of second arm in mm

class Manipulator{
public:	
	Manipulator(int IDOne ,int IDTwo,int IDThree,int IDFour) : one(IDOne, SERVOMODE), two(IDTwo, SERVOMODE), three(IDThree, SERVOMODE), 
	four(IDFour, SERVOMODE){theta1 = 0; theta2 = 0; theta3 = 0;};
	void goToPosition(int, int, int);
	void setAngles(float, float, float);
private:
	float theta1;
	float theta2;
	float theta3;
	Motor one;
	Motor two;
	Motor three;
	Motor four;
};

#endif
