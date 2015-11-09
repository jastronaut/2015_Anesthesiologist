#include "Catapult.h"

Catapult::Catapult()
{
	armManip = new ManipArm();
	choochooTalon = new CANTalon(Catapult_MOTOR_CHANNEL);	
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

	safety = 0;
	fire = 0;

	killSwitchA = true;
	killSwitchB = true;
}

Catapult::~Catapult()
{
	delete choochooTalon;
	delete timer;
	
	choochooTalon = NULL;
	timer = NULL;
}

void Catapult::launchBall()
{	
	fire = oi->joyDrive->GetAxis(FIRE_BUTTON);
	safety = oi->joyDrive->GetAxis(SAFETY_BUTTON);
	killSwitchA = oi->joyDrive->GetRawButton(KILL_SWITCH_A);
	killSwitchB = oi->joyDrive->GetRawButton(KILL_SWITCH_B);

	switch(launchState)	
	{
	case STATE_OFF:	
		choochooMotor->Set(0);
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
		choochooMotor->Set(0);
		
		if(lastPressed && (fire == 0) && (safety == 0))
		{
			lastPressed = false;
		}
		if((fire == 1) && (safety == 1) && !lastPressed)
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
			choochooMotor->Set(-1);
		}
		else
		{
			choochooMotor->Set(SLOW_SPEED);
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
		choochooMotor->Set(0);
		
		if(lastPressed && (fire == 0) && (safety == 0))
		{
			lastPressed = false;
		}
		if((fire == 1) && (safety == 1) && !lastPressed && manipulator->getArmPosition() == true)//true?
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
			choochooMotor->Set(-1);
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
		choochooMotor->Set(-1);
	}
	else
	{
		choochooMotor->Set(0);
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
		choochooMotor->Set(-1);
	}
	else
	{
		choochooMotor->Set(0);
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
		choochooMotor->Set(-1);
	}
	
	if(pulseSwitch->Get() == 1)
	{
		lastPulse = true;
	}
	if(pulseSwitch->Get() == 0 && lastPulse)
	{
		choochooMotor->Set(0);
	}
}
