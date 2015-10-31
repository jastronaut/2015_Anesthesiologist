#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

#include "Manipulator/ManipArm.h"

class Autonomous
{
public:
	Autonomous();
	~Autonomous();

	void shootShootDrive();
	void shootDriveShoot();
	void selectAutonomous(int select);

	ManipArm* armManip;


private:
};

#endif