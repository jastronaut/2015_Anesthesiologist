#ifndef CATAPULT_H_
#define CATAPULT_H_
#include "../Manipulator/ManipArm.h"
#include "../Macros.h"
	
class Catapult
{
public:
	Catapult();
	~Catapult();
	
	void launchBall(bool launchTrigger, bool safetySwitch, bool killSwitchA, bool killSwitchB);
	
	void autoFirstLaunch();
	void autoSecondLaunch();
	void autoReset();
		
	CANTalon *catapultMotor;
	int launchState;
	int autoLaunchState;
	Timer *timer;
	
private:
	DigitalInput *pulseSwitch;
	ManipArm* armManip;
	
	double initTime;
	double currentTime;
	bool init;
	bool autonInit1;
	bool autonInit2;
	bool lastPulse;
	bool lastPressed;
	
};
#endif
