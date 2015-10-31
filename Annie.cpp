#include "WPILib.h"

class Annie: public IterativeRobot
{
private:
	//LiveWindow *lw; do we need this?
	
	void RobotInit()
	{
		//lw = LiveWindow::GetInstance(); wat
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
