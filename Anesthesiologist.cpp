#include "AnesthesiologistDrive.h"
#include "AnesthesiologistManipulator.h"
#include "AnesthesiologistLauncher.h"
#include "AnesthesiologistOperatorInterface.h"
#include "AnesthesiologistMacros.h"


int step = 0;
	//autonomous
bool autonInit = true;
double autonInitTime = 0;
	//timer wait
bool isWait = false;
bool bTimerInit = true;
double initWaitTime = 0;
double currentWaitTime = 0;
	//Latches
bool bTimerLatch = false;
bool bCameraLatch = false;

class Anesthesiologist: public IterativeRobot
{
	AnesthesiologistDrive *drive;
	AnesthesiologistManipulator *manipulator;
	AnesthesiologistLauncher *launcher;
	AnesthesiologistOperatorInterface *oi;
	Compressor *comp599;
	Timer *timer;	
	
public:	
	Anesthesiologist()
	{
		manipulator = new AnesthesiologistManipulator();
		launcher = new AnesthesiologistLauncher(manipulator);
		oi = new AnesthesiologistOperatorInterface();
		drive = new AnesthesiologistDrive(oi);
		comp599 = new Compressor(1, 1, 1, 2); 	
		timer = new Timer();
				
		oi->dashboard->init();
		comp599->Start();
	}
	
	void RobotInit()
	{
	
	}
	
	void DisabledInit()
	{
		
	}
	
	void AutonomousInit()
	{
		step = 0;
		autonInit = true;
		autonInitTime = 0;
		timer->Start();
	}
	
	void TeleopInit()
	{
		step = 0;
		drive->setLinVelocity(0);
		drive->setTurnSpeed(0, false);
		drive->drive();
		comp599->Start();
		timer->Start();		
	}
	
	void TestInit()
	{
	
	}
	
	void DisabledPeriodic()
	{
		step = 0;
		smartDashboardPrint();
	}
	
	void AutonomousPeriodic()
	{	/*	
		if(autonInit) 
		{
			autonInitTime = timer->Get();
			autonInit = false;
		}
		
		smartDashboardPrint();
		*/
		drive->drive();	
	}
	
	void TeleopPeriodic()
	{
		teleDrive();
		smartDashboardPrint();
	}
	
	void TestPeriodic()
	{
	
	}

	void teleDrive()
	{
		if(!isWait)
		{
			drive->setLinVelocity(oi->getDriveJoystick()->GetY(Joystick::kRightHand));
			drive->setTurnSpeed(oi->getDriveJoystick()->GetX(Joystick::kRightHand), oi->getDriveJoystickButton(3));
			drive->drive();
		
			drive->shift(oi->getDriveJoystickButton(8), oi->getDriveJoystickButton(9));
			manipulator->moveArm(oi->getManipJoystickButton(6), oi->getManipJoystickButton(7));
			manipulator->intakeBall(oi->getManipJoystickButton(3), oi->getManipJoystickButton(2), (oi->getManipJoystick()->GetThrottle()+1)/2);
			launcher->launchBall(oi->getDriveJoystickButton(1), oi->getDriveJoystickButton(2), oi->getDriveJoystickButton(10), oi->getDriveJoystickButton(11));
			toggleCompressor(oi->getDriveJoystickButton(6), oi->getDriveJoystickButton(7));
		}
		
			//camera motor mount
		if(oi->getManipJoystickButton(10))
		{
			bCameraLatch = true;
		}
		else if(oi->getManipJoystickButton(11))
		{
			bCameraLatch = false;
		}	
		manipulator->toggleCameraPosition(bCameraLatch);
			
	}
	
	void wait(double secToWait)
	{
		currentWaitTime = timer->Get();
		if(bTimerInit)
		{
			initWaitTime = currentWaitTime;
			bTimerInit = false;
			isWait = true;
		}
		if(currentWaitTime < secToWait + initWaitTime)
		{
			isWait = true;
		}
		else
		{
			isWait = false;
			bTimerInit = true;
			bTimerLatch = false;
		}
		currentWaitTime = timer->Get();
	}
	
	void toggleCompressor(bool start, bool stop)
	{
		if(start)
		{
			comp599->Start();		
		}
		else if(stop)
		{
			comp599->Stop();
		}
	}
	
	void smartDashboardPrint()
	{ 
		oi->dashboard->PutNumber("Drive Linear Speed: ", drive->getLinVelocity());
		oi->dashboard->PutNumber("Drive Turn Speed: ", drive->getTurnSpeed());
		oi->dashboard->PutNumber("Timer: ", timer->Get());
		oi->dashboard->PutNumber("Pot Raw Value: ", manipulator->pot->GetVoltage());
		oi->dashboard->PutBoolean(" Wait (Motors Disabled)", isWait);
		oi->dashboard->PutBoolean(" Compressor", comp599->Enabled());
		oi->dashboard->PutString("Arm Position: ", manipulator->getArmPosition() ? "Intake" : "Stored");
		oi->dashboard->PutString("Shift State: ", drive->getShiftState() ? "High" : "Low");
		oi->dashboard->PutString("Launch State: ", launcher->launchState > 0 ? (launcher->launchState == 1 ? "HOLD" : (launcher->launchState == 2 ? "RESET" : (launcher->launchState == 3 ? "COCKED" : "FIRE"))) : "OFF");
		oi->dashboard->PutString("Camera Position: ", manipulator->getCameraPosition() > 0 ? ((manipulator->getCameraPosition() == 2) ? "Forward" : "Back") : "Inbetween");
		oi->dashboard->PutBoolean(" Ready to Fire", launcher->launchState == STATE_COCKED ? true : false);
	}	
};

START_ROBOT_CLASS(Anesthesiologist);
