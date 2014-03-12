#include "motor.h"

#define NO_TURN		0
#define LEFT_TURN	1
#define RIGHT_TURN	2

#define TURN_MAGNITUDE	0.5f

//put ID of the wheels here
#define FRONT_RIGHT_WHEEL	1
#define BACK_RIGHT_WHEEL	3
#define FRONT_LEFT_WHEEL	0
#define BACK_LEFT_WHEEL		2

class Car{

public:
	Car() : frontRightWheel(FRONT_RIGHT_WHEEL, WHEELMODE), frontLeftWheel(FRONT_LEFT_WHEEL, WHEELMODE),
	backRightWheel(BACK_RIGHT_WHEEL, WHEELMODE), backLeftWheel(BACK_LEFT_WHEEL, WHEELMODE){turn = NO_TURN; speed = 0; direction = 0;};
	void setSpeed(int, bool);
	void turnCar(int);
private:
	int direction;
	int speed;
	int turn;
	Motor frontRightWheel;
	Motor frontLeftWheel;
	Motor backRightWheel;
	Motor backLeftWheel;
};
