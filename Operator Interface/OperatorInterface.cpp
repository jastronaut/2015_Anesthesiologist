#include "OperatorInterface.h"

OperatorInterface::OperatorInterface()
{
	joyDrive = new Joystick(0);

	dashboard->init(); 
}

OperatorInterface::~OperatorInterface()
{
	delete joyDrive;
	delete joyManip;
	
	joyDrive = NULL;
	joyManip = NULL;	
	dashboard = NULL;
}

SmartDashboard* OperatorInterface::getDashboard()
{
	return dashboard;
}
