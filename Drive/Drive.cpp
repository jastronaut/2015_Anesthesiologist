#include "Drive.h"

Drive::Drive()
{
	//if(opInt) oi = opInt;
	
	shifter = new DoubleSolenoid(PNEUMATICS_24V_SLOT, SHIFTER_SOLENOID_CHANNEL_A, SHIFTER_SOLENOID_CHANNEL_B);   
	shifter->Set(DoubleSolenoid::kReverse);
	
	frontLeftMotor = new Talon(FRONT_LEFT_MOTOR_CHANNEL);   
	rearLeftMotor = new Talon(REAR_LEFT_MOTOR_CHANNEL);   
	frontRightMotor = new Talon(FRONT_RIGHT_MOTOR_CHANNEL); 
	rearRightMotor = new Talon(REAR_RIGHT_MOTOR_CHANNEL);
		
	timer = new Timer();
	timer->Start();
}

Drive::~Drive()
{
	delete shifter;
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;
	delete timer;
	
	shifter = NULL;
	frontLeftMotor = NULL;
	rearLeftMotor = NULL;
	frontRightMotor = NULL;
	rearRightMotor = NULL;
	timer = NULL;
}

void Drive::shift(bool highButton, bool lowButton)
{	
	if(lowButton)
		shifter->Set(DoubleSolenoid::kForward);
	else if(highButton)
		shifter->Set(DoubleSolenoid::kReverse);
}

bool Drive::getShiftState()
{
	//iflow gear
	if(shifter->Get() == DoubleSolenoid::kForward)
		return true;
	return false;
}

float Drive::setLinVelocity(float linVal)
{
	if(linVal > DEADZONE)
		return linVal;
	else if(linVal < -DEADZONE)
		return linVal;
	else 
		return 0; //NEUTRAL
}

float Drive::setTurnSpeed(float turn, bool turboButton)
{
	if((turn > DEADZONE && !turboButton) || (turn < -DEADZONE && !turboButton)) 
		return turn * REDUCTION;
	if(turn < DEADZONE && turn > -DEADZONE) 
		return 0; //NEUTRAL
	if((turn > DEADZONE && turboButton) || (turn < -DEADZONE && turboButton)) 
		return turn;
}

void Drive::setLeftMotors(float velocity)
{
	frontLeftMotor->Set(-velocity);
	rearLeftMotor->Set(-velocity);
}

void Drive::setRightMotors(float velocity)
{
	frontRightMotor->Set(velocity);
	rearRightMotor->Set(velocity);
}

void Drive::drive(float joyY, float joyX)
{
	leftCmd = setLinVelocity(joyY +  joyX);
	rightCmd = setLinVelocity(joyY - joyX);
	
	setLeftMotors(leftCmd);
	setRightMotors(rightCmd);
}
