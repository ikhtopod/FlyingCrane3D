#pragma once

#include "Camera.h"
#include "Projection.h"


class TargetCamera : public Camera {
public:
	static const float DEFAULT_DISTANCE;
	static const float MIN_DISTANCE;
	static const float MAX_DISTANCE;
	static const float STEP_DISTANCE;

	static const float CONSTRAINT_MOUSE;

private:
	glm::vec3 targetPosition {};
	float distance;

	bool middleMousePressed = false;
	bool keyShiftPressed = false;

private:
	void updatePosition();
	void normalizeTargetPosition();
	void constraintCursor();

public:
	TargetCamera();

	glm::vec3 getTargetPosition();
	float getDistance();

	void setTargetPosition(glm::vec3 _targetPosition);
	void setDistance(float _distance);

	void move(float xPos, float yPos);
	void zoom(float xOffset, float yOffset);

public:
	virtual void spin() override;
	virtual void spin(float xPos, float yPos) override;
	virtual void keyboardInput() override;
	virtual void mouseInput(float xPos, float yPos) override;
	virtual void mouseButtonInput(int button, int action, int mods) override;
	virtual void mouseScrollInput(float xOffset, float yOffset) override;
};
