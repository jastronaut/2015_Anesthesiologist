#include "Drive.h"

AnesthesiologistDrive::AnesthesiologistDrive(AnesthesiologistOperatorInterface *opInt)
{
	//if(opInt) oi = opInt;
	
	linearVelocity = 0;
	turnSpeed = 0;
	
	shifter = new DoubleSolenoid(PNEUMATICS_24V_SLOT, SHIFTER_SOLENOID_CHANNEL_A, SHIFTER_SOLENOID_CHANNEL_B);   
	shifter->Set(DoubleSolenoid::kReverse);
	
	frontLeftMotor = new Talon(FRONT_LEFT_MOTOR_CHANNEL);   
	rearLeftMotor = new Talon(REAR_LEFT_MOTOR_CHANNEL);   
	frontRightMotor = new Talon(FORNT_RIGHT_MOTOR_CHANNEL); 
	rearRightMotor = new Talon(REAR_RIGHT_MOTOR_CHANNEL);

	oi = new OperatorInterface();
		
	timer = new Timer();
	timer->Start();
}

AnesthesiologistDrive::~AnesthesiologistDrive()
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

void AnesthesiologistDrive::shift(bool highButton, bool lowButton)
{	
	if(lowButton)
		shifter->Set(DoubleSolenoid::kForward);
	else if(highButton)
		shifter->Set(DoubleSolenoid::kReverse);
}

bool AnesthesiologistDrive::getShiftState()
{
	//iflow gear
	if(shifter->Get() == DoubleSolenoid::kForward)
		return true;
	return false;
}

float AnesthesiologistDrive::setLinVelocity(float linVal)
{
	if(linVal > DEADZONE)
		return linVal;
	else if(linVal < -DEADZONE)
		return linVal;
	else 
		return 0; //NEUTRAL
}

float AnesthesiologistDrive::setTurnSpeed(float turn, bool turboButton)
{
	if((turn > DEADZONE && !turboButton) || (turn < -DEADZONE && !turboButton)) 
		return turn * REDUCTION;
	if(turn < DEADZONE && turn > -DEADZONE) 
		return 0; //NEUTRAL
	if((turn > DEADZONE && turboButton) || (turn < -DEADZONE && turboButton)) 
		return turn;
}

void AnesthesiologistDrive::setLeftMotors(float velocity)
{
	frontLeftMotor->Set(-velocity);
	rearLeftMotor->Set(-velocity);
}

void AnesthesiologistDrive::setRightMotors(float velocity)
{
	frontRightMotor->Set(velocity);
	rearRightMotor->Set(velocity);
}

void AnesthesiologistDrive::drive()
{
	leftCmd = setLinVelocity(oi->joyDrive->GetRawAxis(FORWARD_Y_AXIS)) +  setTurnSpeed(oi->joyDrive->GetRawAxis(TURN_X_AXIS));
	rightCmd = setLinVelocity(oi->joyDrive->GetRawAxis(FORWARD_Y_AXIS)) - setTurnSpeed(oi->joyDrive->GetRawAxis(TURN_X_AXIS));
	
	setLeftMotors(leftCmd);
	setRightMotors(rightCmd);
}
