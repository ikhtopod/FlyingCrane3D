#pragma once

#include "Camera.h"


class FreeCamera : public Camera {
private:
	glm::vec2 lastMousePosition {};

public:
	virtual void keyboardInput() override;
	virtual void mouseInput(float xPos, float yPos) override;
};

