#include "motor.h"

#define NO_TURN		0
#define LEFT_TURN	1
#define RIGHT_TURN	2

#define TURN_MAGNITUDE	0.5f

#define IDLE_MODE	0
#define FRONT_OFF_MODE	1
#define BACK_OFF_MODE	2
#define ALL_OFF_MODE	3

class Car{

public:
	Car(int FR,int FL,int BR,int BL) : frontRightWheel(FR, WHEELMODE), frontLeftWheel(FL, WHEELMODE),
	backRightWheel(BR, WHEELMODE), backLeftWheel(BL, WHEELMODE){turn = NO_TURN; speed = 0; direction = 0; mode = IDLE_MODE;};
	void setSpeed(int, bool);
	int getSpeed();
	void turnCar(int);
	void setMode(int);
	int getMode();
private:
	int direction;
	int speed;
	int turn;
	int mode;
	Motor frontRightWheel;
	Motor frontLeftWheel;
	Motor backRightWheel;
	Motor backLeftWheel;
};