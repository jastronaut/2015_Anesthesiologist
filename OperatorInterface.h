#ifndef OPERATOR_INTERFACE_H_
#define OPERATOR_INTERFACE_H_


#include "WPILib.h"
#include "Macros.h"

class OperatorInterface
{
	
public:
	OperatorInterface();	
	~OperatorInterface();
	
	SmartDashboard* getDashboard();
	
private:
	Joystick *joyDrive;
	Joystick *joyManip;

	SmartDashboard* dashboard;
};
#endif
