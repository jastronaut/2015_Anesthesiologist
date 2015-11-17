#include "ManipCamera.cpp"

ManipCamera::ManipCamera()
{
	cameraMotor = new Victor(CAMERA_VICTOR_CHANNEL);
	pot = new AnalogChannel(1, POT_CHANNEL);
}

ManipCamera::ManipCamera()
{
	delete cameraMotor;
	delete pot;

	cameraMotor = NULL;
	pot = NULL;
}


int ManipCamera::getCameraPosition()
{
	if(pot->GetVoltage() > POT_UPPER_LIMIT - POT_DEADZONE_HIGH)
	{
		return 2;
	}
	else if(pot->GetVoltage() < POT_LOWER_LIMIT + POT_DEADZONE_LOW)
	{
		return 1;
	}
	return 0;
}

void ManipCamera::toggleCameraPosition(bool isForward)
{
	bool isForwardLimit = false;
	bool isBackLimit = false;
	
	if(pot->GetVoltage() > POT_UPPER_LIMIT - POT_DEADZONE_HIGH)
	{
		isBackLimit = true;
	}
	else if(pot->GetVoltage() < POT_LOWER_LIMIT + POT_DEADZONE_LOW)
	{
		isForwardLimit = true;
	}
	else
	{
		isForwardLimit = false;
		isBackLimit = false;
	}
	
	if(isForwardLimit || isBackLimit)
	{
		cameraMotor->Set(0, SYNC_STATE_OFF);
	}
	if(isForward && !isForwardLimit)
	{
		cameraMotor->Set(1, SYNC_STATE_OFF);
	}
	if(!isForward && !isBackLimit)
	{
		cameraMotor->Set(-1, SYNC_STATE_OFF);
	}
	
}