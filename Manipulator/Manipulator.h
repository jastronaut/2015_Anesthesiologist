#ifndef MANIPULATOR_H_
#define MANIPULATOR_H_
#include "../Macros.h"
#include "../Operator\ Interface/OperatorInterface.h"
#include "ManipArm.h"
#include "ManipCamera.h"

class Manipulator
{
public:
	Manipulator();
	~Manipulator();

	void intakeBall(bool intake, bool outtake, double speed);
	void toggleCompressor(bool start);


	// DigitalInput *intakeSwitch;
	Talon *intakeRoller;
	Timer *timer;
	comp599 = new Compressor(1, 1, 1, 2); 
	int step;

private:
	DoubleSolenoid *intakeArm;

	ManipArm* arm;
	ManipCamera* camera;
	OperatorInterface* oi;

	int count;
};

#endif