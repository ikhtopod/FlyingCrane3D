#pragma once

#include "Util.h"
#include "DeltaTime.h"
#include "Transform.h"
#include "Axis.h"


class ICamera {
public:
	virtual void spin() = 0;
	virtual void spin(float xPos, float yPos) = 0;
	virtual void keyboardInput() = 0;
	virtual void mouseInput(float xPos, float yPos) = 0;
	virtual void mouseButtonInput(int button, int action, int mods) = 0;
	virtual void mouseScrollInput(float xOffset, float yOffset) = 0;
};


class Camera : public ICamera {
public:
	static const float DEFAULT_MOUSE_PITCH;
	static const float MIN_MOUSE_PITCH;
	static const float MAX_MOUSE_PITCH;

	static const float DEFAULT_MOUSE_YAW;
	static const float MIN_MOUSE_YAW;
	static const float MAX_MOUSE_YAW;

	static const float DEFAULT_MOUSE_ROLL;

	static const float DEFAULT_SPEED_MOVEMENT;
	static const float STEP_SPEED_MOVEMENT;

	static const float DEFAULT_MOUSE_SENSITIVITY_X;
	static const float DEFAULT_MOUSE_SENSITIVITY_Y;

	static const float DEFAULT_CAMERA_FOV;
	static const float MIN_CAMERA_FOV;
	static const float MAX_CAMERA_FOV;

protected:
	Transform transform {};
	Axis axis {};

	glm::vec2 lastMousePosition {};

	float speedMovement;
	glm::vec2 mouseSensitivity;
	float fov;

protected:
	void updateCameraVectors();

public:
	Camera();
	virtual ~Camera() = default;

	Transform& getTransform();
	Axis& getAxis();
	glm::vec2 getLastMousePosition() const;
	float getFoV() const;
	float getSpeedMovement() const;

	void setTransform(const Transform& _transform);
	void setAxis(const Axis& _axis);
	void setLastMousePosition(const glm::vec2& _LastMousePosition);

	glm::mat4 GetViewMatrix() const;
};
