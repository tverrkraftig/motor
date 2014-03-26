#include <stdio.h>
#include <math.h>
#include "manipulator.h"

using namespace std;

#define PI 3.14159265

void Manipulator::goToPosition(int x, int y, int z){
	int s3, c3;
	c3 = (z*z + y*y - D2*D2 - D3*D3)/(D2*D3);
	s3 = sqrt(1-c3*c3);
	theta3 = atan2(s3,c3);
	theta2 = PI/2 - atan2(D3*s3, D2+D3*c3)-atan2(z,y);
	theta1 = atan2(x,y);
	one.setGoalPosition(200);
	two.setGoalPosition(200);
	three.setGoalPosition(200);
}
