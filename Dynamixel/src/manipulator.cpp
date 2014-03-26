#include <stdio.h>
#include <math.h>
#include "manipulator.h"

using namespace std;

#define PI 3.14159265

void Manipulator::goToPosition(int x, int y, int z){

	//return error if beyond max
	if((x*x+y*y+z*z) > (D2+D3)*(D2+D3))
	{
		printf("invalid position!\n");
		return;
	}
	
	float s3, c3, l;
	int dummy;
	
	l = sqrt(x*x+y*y);
	c3 = (z*z + l*l - D2*D2 - D3*D3)/(2*D2*D3);
	s3 = sqrt(1-c3*c3);
	
	theta3 = atan2(s3,c3);
	theta2 = PI/2 - atan2(D3*s3, D2+D3*c3)-atan2(z,l);
	theta1 = atan2(x,y);

	dummy = (float)(theta1*511/PI+511);
	one.setGoalPosition(dummy);
	printf("one: %d\n",dummy);

	dummy = (float)(theta2*511/PI+511);
	two.setGoalPosition(dummy);
	printf("two: %d\n",dummy);

	dummy = (float)(theta3*511/PI+511);
	three.setGoalPosition(dummy);
	printf("three: %d\n",dummy);
}
