#include "OperatorInterface.h"

Joystick *OperatorInterface::getDriveJoystick()
{
    return joyDrive;
}

Joystick *OperatorInterface::getManipJoystick()
{
    return joyManip;
}

bool OperatorInterface::getDriveJoystickButton(UINT8 button)
{
	 if(joyDrive->GetRawButton(button))
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }
}

bool OperatorInterface::getManipJoystickButton(UINT8 button)
{
	if( joyManip->GetRawButton(button) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float OperatorInterface::getBatteryVoltage()
{
	return DriverStation::GetInstance()->GetBatteryVoltage();
}

OperatorInterface::OperatorInterface()
{
	joyDrive = new Joystick(1);
	joyManip = new Joystick(2);

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
