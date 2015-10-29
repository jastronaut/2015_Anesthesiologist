#include "ManipArm.h"

ManipArm::ManipArm()
{
	intakeArm = new DoubleSolenoid(INTAKE_ARM_SOLENOID_CHANNEL_A, INTAKE_ARM_SOLENOID_CHANNEL_B);
}

ManipArm::~ManipArm()
{
	delete intakeArm;

	intakeArm = NULL;
}

void ManipArm::moveArm(bool isIntake, bool isStored)
{
	if(isIntake)
	{
		intakeArm->Set(DoubleSolenoid::kReverse);
	}
	else if(isStored)
	{
		intakeArm->Set(DoubleSolenoid::kForward);
	}
}

bool ManipArm::getArmPosition()
{
	if(intakeArm->Get() == DoubleSolenoid::kReverse)
	{
		return true;
	}
	return false;
}