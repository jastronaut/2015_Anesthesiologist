#include "Autonomous.h"


Autonomous::Autonomous()
{
	armManip = new ManipArm();
}

Autonomous::~Autonomous()
{

}

void Autonomous::shootShootDrive()
{
	//ignores hot goal, 2 ball auton (shoot, shoot, drive)
	if(timer->Get() > 0 + autonInitTime && timer->Get() < 1 + autonInitTime)
	{
		armManip->moveArm(true, false);
	}
	if(timer->Get() > 1.2 + autonInitTime && timer->Get() < 1.5 + autonInitTime)
	{
		launcher->autoFirstLaunch();
	}
	if(timer->Get() > 1.5 + autonInitTime && timer->Get() < 3.5  + autonInitTime)
	{
		launcher->autoReset();
	}
	if(timer->Get() > 3.5 + autonInitTime && timer->Get() < 5 + autonInitTime)
	{
		manipulator->intakeRoller->Set(1);
	}
	if(timer->Get() > 5 + autonInitTime && timer->Get() < 6 + autonInitTime)
	{
		manipulator->intakeRoller->Set(0);
		armManip->moveArm(false, true);
	}		
	if(timer->Get() > 6.2 + autonInitTime && timer->Get() < 7.2 + autonInitTime)
	{
		manipulator->intakeRoller->Set(1);
		armManip->moveArm(true, false);
	}
	if(timer->Get() > 7.4 + autonInitTime && timer->Get() < 7.7 + autonInitTime)
	{
		manipulator->intakeRoller->Set(0);
		launcher->autoSecondLaunch();
	}
	if(timer->Get() > 7.8 + autonInitTime && timer->Get() < 9.8 + autonInitTime)
	{
		drive->setLinVelocity(-1);
	}
	if(timer->Get() > 9.8 + autonInitTime && timer->Get() < 10 + autonInitTime)
	{
		drive->setLinVelocity(0);
	}
}

void Autonomous::shootDriveShoot()
{
	if(timer->Get() > 0 + autonInitTime && timer->Get() < 1 + autonInitTime)
		{
			manipulator->moveArm(true, false);
		}
		if(timer->Get() > 1.2 + autonInitTime && timer->Get() < 1.5 + autonInitTime)
		{
			launcher->autoFirstLaunch();
		}
		if(timer->Get() > 1.5 + autonInitTime && timer->Get() < 3.5  + autonInitTime)
		{
			launcher->autoReset();
		}
		if(timer->Get() > 3.5 + autonInitTime && timer->Get() < 5 + autonInitTime)
		{
			manipulator->intakeRoller->Set(1);
		}
		if(timer->Get() > 5 + autonInitTime && timer->Get() < 6 + autonInitTime)
		{
			manipulator->intakeRoller->Set(0);
			manipulator->moveArm(false, true);
		}		
		if(timer->Get() > 6 + autonInitTime && timer->Get() < 7 + autonInitTime)
		{
			drive->setLinVelocity(-1);
		}
		if(timer->Get() > 7.2 + autonInitTime && timer->Get() < 8.2 + autonInitTime)
		{
			drive->setLinVelocity(0);
			manipulator->intakeRoller->Set(1);
			manipulator->moveArm(true, false);
		}
		if(timer->Get() > 8.4 + autonInitTime && timer->Get() < 8.7 + autonInitTime)
		{
			manipulator->intakeRoller->Set(0);
			launcher->autoSecondLaunch();
		}	
}

void Autonomous::ignoreHotGoal()
{
	if(timer->Get() > 0 + autonInitTime && timer->Get() < 2 + autonInitTime)
	{
		drive->setLinVelocity(-1);
	}
	if(timer->Get() > 2 + autonInitTime && timer->Get() < 3 + autonInitTime)
	{
		drive->setLinVelocity(0);
		manipulator->intakeRoller->Set(1);
		manipulator->moveArm(true, false);
	}
	if(timer->Get() > 6 + autonInitTime && timer->Get() < 6.3 + autonInitTime)
	{
		manipulator->intakeRoller->Set(0);
		launcher->autoFirstLaunch();
	}
}