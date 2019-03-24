#pragma once

#include "Camera.h"


class FreeCamera : public Camera {
public:
	void changeSpeed(float xOffset, float yOffset);
	void move();

public:
	virtual void spin() override;
	virtual void spin(float xPos, float yPos) override;
	virtual void keyboardInput() override;
	virtual void mouseInput(float xPos, float yPos) override;
	virtual void mouseButtonInput(int button, int action, int mods) override;
	virtual void mouseScrollInput(float xOffset, float yOffset) override;
};

