#ifndef MANIP_ARM_H_
#define MANIP_ARM_H_

class ManipArm
{
public:
	ManipArm();
	~ManipArm();

	void moveArm(bool isIntake, bool isStored);
	bool getArmPosition();

private:
	DoubleSolenoid* intakeArm;
};

#endif