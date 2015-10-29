#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_

#include "ManipArm.h"
#include "ManipCamera.h"

class Manipulator
{
public:
	Manipulator();
	~Manipulator();

	void intakeBall(bool intake, bool outtake, double speed);


	// DigitalInput *intakeSwitch;
	Talon *intakeRoller;
	Timer *timer;

	int step;

private:
	DoubleSolenoid *intakeArm;

	ManipArm* arm;
	ManipCamera* camera; 
};

#endif