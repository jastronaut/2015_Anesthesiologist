#include "Catapult.h"

Catapult::Catapult()
{
	armManip = new ManipArm();
	catapultMotor = new CANTalon(1, Catapult_MOTOR_CHANNEL);	
	pulseSwitch = new DigitalInput(1, PULSE_SWITCH_CHANNEL);
	// breakout board  ,talonlllllll
	
	lastPulse = false;
	launchState = STATE_HOLD;
	autoLaunchState = STATE_COCKED;	
	
	init = true;
	autonInit1 = true;
	autonInit2 = true;
	lastPressed = true;
	
	timer = new Timer();
	timer->Start();
	initTime = 0;
	currentTime = 0;
}

Catapult::~Catapult()
{
	delete CatapultMotor;
	delete pulseSwitch;
	delete timer;
	
	CatapultMotor = NULL;
	pulseSwitch = NULL;
	timer = NULL;
}

void Catapult::launchBall(bool launchTrigger, bool safetySwitch, bool killSwitchA, bool killSwitchB)
{	
	switch(launchState)	
	{
	case STATE_OFF:	
		CatapultMotor->Set(0);
		if(lastPressed && !killSwitchA && !killSwitchB)
		{
			lastPressed = false;
		}
		if(killSwitchA && killSwitchB && !lastPressed)
		{
			lastPressed = true;
			launchState = STATE_HOLD;
		}
		break;
	case STATE_HOLD:
		
		if(killSwitchA && killSwitchB)
		{
			launchState = STATE_OFF;
		}
		
		init = true;
		CatapultMotor->Set(0);
		
		if(lastPressed && !launchTrigger && !safetySwitch)
		{
			lastPressed = false;
		}
		if(launchTrigger && safetySwitch && !lastPressed)
		{
			lastPressed = true;
			launchState = STATE_RESET;
		}
		break;
	case STATE_RESET:
		
		if(killSwitchA && killSwitchB) 
		{
			launchState = STATE_OFF;
		}
		if(init)
		{
			initTime = timer->Get();
			init = false;
		}
		currentTime = timer->Get();
		
		if(currentTime < RESET_TIME + initTime)
		{
			CatapultMotor->Set(-1);
		}
		else
		{
			CatapultMotor->Set(SLOW_SPEED);
		}
		
		if(pulseSwitch->Get() == 1)
		{
			lastPulse = true;
		}
		if(pulseSwitch->Get() == 0 && lastPulse)
		{
			launchState = STATE_COCKED;
		}
		break;
	case STATE_COCKED:
		
		if(killSwitchA && killSwitchB) 
		{
			launchState = STATE_OFF;
		}
		init = true;
		CatapultMotor->Set(0);
		
		if(lastPressed && !launchTrigger && !safetySwitch)
		{
			lastPressed = false;
		}
		if(launchTrigger && safetySwitch && !lastPressed && manipulator->getArmPosition() == true)//true?
		{
			lastPressed = true;
			launchState = STATE_FIRE;
		}
		break;
	case STATE_FIRE:
		if(killSwitchA && killSwitchB) 
		{
			launchState = STATE_OFF;
		}
		
		if(init)
		{
			initTime = timer->Get();
			init = false;
		}
		currentTime = timer->Get();
		
		if(currentTime < LAUNCH_TIME + initTime)
		{
			CatapultMotor->Set(-1);
		}
		else
		{
			launchState = STATE_HOLD;
		}
		break;
	default:
		launchState = STATE_OFF;
	}
}

void Catapult::autoFirstLaunch()
{	
	if(autonInit1)
	{
		initTime = timer->Get();
		autonInit1 = false;
	}
	currentTime = timer->Get();
	
	if(currentTime < LAUNCH_TIME + initTime)
	{
		CatapultMotor->Set(-1);
	}
	else
	{
		CatapultMotor->Set(0);
	}
}

void Catapult::autoSecondLaunch()
{	
	if(autonInit2)
	{
		initTime = timer->Get();
		autonInit2 = false;
	}
	currentTime = timer->Get();
	
	if(currentTime < LAUNCH_TIME + initTime)
	{
		CatapultMotor->Set(-1);
	}
	else
	{
		CatapultMotor->Set(0);
	}
}

void Catapult::autoReset()
{
	if(init)
	{
		initTime = timer->Get();
		init = false;
	}
	currentTime = timer->Get();
	
	if(currentTime < RESET_TIME + initTime)
	{
		CatapultMotor->Set(-1);
	}
	
	if(pulseSwitch->Get() == 1)
	{
		lastPulse = true;
	}
	if(pulseSwitch->Get() == 0 && lastPulse)
	{
		CatapultMotor->Set(0);
	}
}
