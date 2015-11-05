#ifndef LAUNCHER_H_
#define LAUNCHER_H_
#include "AnesthesiologistManipulator.h"
#include "AnesthesiologistMacros.h"
	
class Launcher
{
public:
	Launcher(AnesthesiologistManipulator* manip);
	~Launcher();
	
	void launchBall(bool launchTrigger, bool safetySwitch, bool killSwitchA, bool killSwitchB);
	
	void autoFirstLaunch();
	void autoSecondLaunch();
	void autoReset();
		
	Victor *launcherMotor;
	int launchState;
	int autoLaunchState;
	Timer *timer;
	
private:
	DigitalInput *pulseSwitch;
	AnesthesiologistManipulator *manipulator;
	
	double initTime;
	double currentTime;
	bool init;
	bool autonInit1;
	bool autonInit2;
	bool lastPulse;
	bool lastPressed;
	
};
#endif
