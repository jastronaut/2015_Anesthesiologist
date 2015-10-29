#ifndef MANIP_CAMERA_H_
#define MANIP_CAMERA_H_

class ManipCamera
{
public:
	ManipCamera();
	~ManipCamera();

	void toggleCameraPosition(bool isForward);
	int getCameraPosition();

	Victor *cameraMotor;
	AnalogChannel *pot;
};

#endif