#include "Manipulator.h"

Manipulator::Manipulator()
{
	intakeRoller = new Talon(1, INTAKE_ROLLER_CHANNEL);
	//intakeSwitch = new DigitalInput(1, INTAKE_SWITCH_CHANNEL);
	arm = new ManipArm();
	camera = new ManipCamera();
	
	comp599->Start();

	step = 0;
	count = 0;
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

void toggleCompressor(bool start)
{
	// TODO: make this make sense
	if(start)
		count++;
	
	if(count%2 == 0)
		comp599->Stop();
	else
		comp599->Start();
}