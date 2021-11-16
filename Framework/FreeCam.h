#pragma once
#include "Viewer/Camera.h"

class FreeCam :
	public Camera
{
	FreeCam();
	~FreeCam();

	void Update() override;
	void Speed(float move, float rotation);
};

