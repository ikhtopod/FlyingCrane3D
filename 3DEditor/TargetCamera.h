#pragma once

#include "Camera.h"


class TargetCamera : public Camera {
public:
	static const float DEFAULT_DISTANCE;
	static const float MIN_DISTANCE;
	static const float MAX_DISTANCE;
	static const float STEP_DISTANCE;

private:
	glm::vec3 targetPosition;
	float distance;

public:
	TargetCamera();

	glm::vec3 getTargetPosition();
	float getDistance();

	void setTargetPosition(glm::vec3 _targetPosition);
	void setDistance(float _distance);

	void move();
	void spin();
	void zoom();

public:
	virtual void keyboardInput() override;
	virtual void mouseInput(float xPos, float yPos) override;
	virtual void mouseButtonInput(int button, int action, int mods) override;
	virtual void mouseScrollInput(float xOffset, float yOffset) override;
};
