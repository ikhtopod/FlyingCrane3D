#pragma once

#include "Camera.h"


class TargetCamera : public Camera {
public:
	static const float DEFAULT_DISTANCE;
	static const float MIN_DISTANCE;
	static const float MAX_DISTANCE;
	static const float STEP_DISTANCE;

private:
	glm::vec3 targetTransform;
	float distance;

public:
	TargetCamera();

	virtual void keyboardInput() override;
	virtual void mouseInput(float xPos, float yPos) override;
};
