#include "motor.h"

#define D2	7.7f
#define D3	9.4f

class Manipulator{
public:	
	Manipulator(int IDOne ,int IDTwo,int IDThree,int IDFour) : one(IDOne, SERVOMODE), two(IDOne, SERVOMODE), three(IDOne, SERVOMODE), 
	four(IDOne, SERVOMODE){theta1 = 0; theta2 = 0; theta3 = 0;};
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
