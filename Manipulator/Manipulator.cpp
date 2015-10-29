#include "Manipulator.h"
#include "Man"
Manipulator::Manipulator()
{
	intakeRoller = new Talon(1, INTAKE_ROLLER_CHANNEL);
	//intakeSwitch = new DigitalInput(1, INTAKE_SWITCH_CHANNEL);
	
	step = 0;
}

Manipulator::~Manipulator()
{
	delete intakeRoller;
	delete intakeSwitch;
	
	intakeRoller = NULL;
	//intakeSwitch = NULL;
}

void AnesthesiologistManipulator::intakeBall(bool outtake, bool intake, double speed)
{
	bool lastSwitchHit = false;

	if(!lastSwitchHit)
	{
		step = 1;
		if(outtake)
		{
			intakeRoller->Set(-speed, SYNC_STATE_OFF);
		}
		else if(intake)
		{
			intakeRoller->Set(speed, SYNC_STATE_OFF);
		}
		else
		{
			intakeRoller->Set(0, SYNC_STATE_OFF);
		}
	}
}