#include "AnesthesiologistOperatorInterface.h"

AnesthesiologistOperatorInterface::AnesthesiologistOperatorInterface()
{

}

Joystick *AnesthesiologistOperatorInterface::getDriveJoystick()
{
    return joyDrive;
}

Joystick *AnesthesiologistOperatorInterface::getManipJoystick()
{
    return joyManip;
}

bool AnesthesiologistOperatorInterface::getDriveJoystickButton(UINT8 button)
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

bool AnesthesiologistOperatorInterface::getManipJoystickButton(UINT8 button)
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

float AnesthesiologistOperatorInterface::getBatteryVoltage()
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
