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
	
	void drive();
	void setLinVelocity(double linVal);
	double getLinVelocity();
	
	void setTurnSpeed(double turn, bool turboButton);		
	double getTurnSpeed();	
	
	double reduceTurn(double reduceBy);	
	
	void setLeftMotors(double velocity);
	void setRightMotors(double velocity);

	DoubleSolenoid *shifter;
	Timer *timer;
	
private:
	CANTalon *frontLeftMotor;
	CANTalon *rearLeftMotor;
	CANTalon *frontRightMotor;
	CANTalon *rearRightMotor;
	
	//AnesthesiologistOperatorInterface *oi;
	
	double linearVelocity; 
	double turnSpeed;
	double leftCmd;
	double rightCmd;	
};
#endif
