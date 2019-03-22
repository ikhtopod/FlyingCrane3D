#pragma once

#include "Camera.h"


class TargetCamera : public Camera {
public:
	virtual void keyboardInput() override;
	virtual void mouseInput(float xPos, float yPos) override;
};
