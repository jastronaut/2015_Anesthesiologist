#ifndef CATAPULT_H_
#define CATAPULT_H_
#include "../Macros.h"
#include "../Operator\ Interface/OperatorInterface.h"
#include "../Manipulator/ManipArm.h"
	
class Catapult
{
public:
	Catapult();
	~Catapult();
	
	void launchBall(bool launchTrigger, bool safetySwitch, bool killSwitchA, bool killSwitchB);
	
	void autoFirstLaunch();
	void autoSecondLaunch();
	void autoReset();
		
	CANTalon *choochooTalon;
	int launchState;
	int autoLaunchState;
	Timer *timer;
	
private:
	ManipArm* armManip;
	OperatorInterface* oi;
	
	double initTime;
	double currentTime;
	bool init;
	bool autonInit1;
	bool autonInit2;
	bool lastPulse;
	bool lastPressed;
	float fire;
	float safety;
	bool killSwitchB;
	bool killSwitchA;
	
};
#endif
