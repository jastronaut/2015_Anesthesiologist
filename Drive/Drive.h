#ifndef DRIVE_H
#define DRIVE_H
#include "../Macros.h"
#include "../Operator\ Interface/OperatorInterface.h"

class Drive
{
public:
	Drive();
	~Drive();
	
	void shift(bool highButton, bool lowButton);
	bool getShiftState();
	
	float setLinVelocity(float linVal);
	
	float setTurnSpeed(float turn, bool turboButton);	
	
	void setLeftMotors(double velocity);
	void setRightMotors(double velocity);

	void drive(float joyY, float joyX);

	DoubleSolenoid *shifter;
	Timer *timer;

private:
	CANTalon *frontLeftMotor;
	CANTalon *rearLeftMotor;
	CANTalon *frontRightMotor;
	CANTalon *rearRightMotor;
	
	AnesthesiologistOperatorInterface *oi;
	
	float leftCmd;
	float rightCmd;	
};
#endif
