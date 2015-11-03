#ifndef OPERATOR_INTERFACE_H_
#define OPERATOR_INTERFACE_H_


#include "WPILib.h"
#include "AnesthesiologistMacros.h"

#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/NamedSendable.h"
#include "SmartDashboard/Sendable.h"
#include "SmartDashboard/SendableChooser.h"

class AnesthesiologistOperatorInterface
{
	
public:
	AnesthesiologistOperatorInterface();	
	~AnesthesiologistOperatorInterface();
	
	Joystick *getDriveJoystick();
	bool getDriveJoystickButton(UINT8 button);
	bool getDriveJoystickButtonReleased(UINT8 button);

	Joystick *getManipJoystick();		
	bool getManipJoystickButton(UINT8 button);		
	bool getManipJoystickButtonReleased(UINT8 button);
	
	float getBatteryVoltage();
	
	SmartDashboard* getDashboard();
	
private:
	Joystick *joyDrive;
	Joystick *joyManip;

	SmartDashboard* dashboard;
};
#endif
