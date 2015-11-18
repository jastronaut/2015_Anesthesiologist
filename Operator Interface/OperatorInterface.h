#ifndef OPERATOR_INTERFACE_H_
#define OPERATOR_INTERFACE_H_

#include "WPILib.h"
#include "../Macros.h"

class OperatorInterface
{
	
public:
	OperatorInterface();	
	~OperatorInterface();
	
	SmartDashboard* getDashboard();
	
	Joystick *joyDrive;
	Joystick *joyManip;

private:

	SmartDashboard* dashboard;
};
#endif
