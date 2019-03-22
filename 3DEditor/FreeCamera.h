#pragma once

#include "Camera.h"


class FreeCamera : public Camera {
public:
	virtual void keyboardInput() override;
	virtual void mouseInput(float xPos, float yPos) override;
};

