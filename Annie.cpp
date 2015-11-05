#include "WPILib.h"
#include "Drive.h"
#include "Manipulator/Manipulator.h"
#include "Launcher.h"
#include "OperatorInterface.h"
#include "Macros.h"

class Annie: public IterativeRobot
{
private:
	//LiveWindow *lw; do we need this?
	Drive *drive;
	Manipulator *manip;
	Launcher *launcher;
	OperatorInterface *oi;
	Compressor *comp599;
	Timer *timer;

	void RobotInit()
	{
		//lw = LiveWindow::GetInstance(); wat
		drive = new Drive();
		manip = new Manipulator();
		launcher = new Launcher();
		oi = new OperatorInterface();

	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		if(!isWait)
		{
			drive->drive();
			drive->shift(oi->joyDrive->GetRawButton(8), oi->joyDrive->GetRawButton(9));
			

			manipulator->moveArm(oi->joyManip->GetRawButton(6), oi->joyManip->GetRawButton(7));
			manipulator->intakeBall(oi->joyManip->GetRawButton(3), oi->joyManip->GetRawButton(2), (oi->getManipJoystick()->GetThrottle()+1)/2);
			launcher->launchBall(oi->joyDrive->GetRawButton(1), oi->joyDrive->GetRawButton(2), oi->joyDrive->GetRawButton(10), oi->joyDrive->GetRawButton(11));
			toggleCompressor(oi->joyDrive->GetRawButton(6), oi->joyDrive->GetRawButton(7));
		}
		
			//camera motor mount
		if(oi->joyManip->GetRawButton(10))
		{
			bCameraLatch = true;
		}
		else if(oi->joyManip->GetRawButton(11))
		{
			bCameraLatch = false;
		}	
		manip->toggleCameraPosition(bCameraLatch);
	}

	void printSmartDashboard()
	{

	}

	void TestPeriodic()
	{
		//lw->Run(); ok then
	}
};

START_ROBOT_CLASS(Annie);
