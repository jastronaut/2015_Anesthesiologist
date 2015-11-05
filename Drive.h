#ifndef ANESTHESIOLOGIST_DRIVE_H
#define ANESTHESIOLOGIST_DRIVE_H
#include "AnesthesiologistMacros.h"
#include "AnesthesiologistOperatorInterface.h"

class AnesthesiologistDrive
{
public:
	AnesthesiologistDrive(AnesthesiologistOperatorInterface *opInt = NULL);
	~AnesthesiologistDrive();
	
	void shift(bool highButton, bool lowButton);
	bool getShiftState();
	
	float setLinVelocity(float linVal);
	
	float setTurnSpeed(float turn, bool turboButton);	
	
	void setLeftMotors(double velocity);
	void setRightMotors(double velocity);

	void drive();

	DoubleSolenoid *shifter;
	Timer *timer;

private:
	CANTalon *frontLeftMotor;
	CANTalon *rearLeftMotor;
	CANTalon *frontRightMotor;
	CANTalon *rearRightMotor;
	
	AnesthesiologistOperatorInterface *oi;
	
	float linearVelocity; 
	float turnSpeed;
	float leftCmd;
	float rightCmd;	
};
#endif
