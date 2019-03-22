#pragma once

#include "Util.h"
#include "DeltaTime.h"
#include "Transform.h"
#include "Axis.h"


class Camera {
public:
	static const float DEFAULT_MOUSE_PITCH;
	static const float MIN_MOUSE_PITCH;
	static const float MAX_MOUSE_PITCH;

	static const float DEFAULT_MOUSE_YAW;
	static const float MIN_MOUSE_YAW;
	static const float MAX_MOUSE_YAW;

	static const float DEFAULT_MOUSE_ROLL;

	static const float DEFAULT_SPEED_MOVEMENT;
	static const float DEFAULT_MOUSE_SENSITIVITY_X;
	static const float DEFAULT_MOUSE_SENSITIVITY_Y;

	static const float DEFAULT_CAMERA_FOV;
	static const float MIN_CAMERA_FOV;
	static const float MAX_CAMERA_FOV;

	static const glm::vec3 DEFAULT_CAMERA_POSITION;


protected:
	Transform transform {};
	Axis axis {};

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

	float getFoV();
	float getSpeedMovement();

	glm::mat4 GetViewMatrix();

	void keyboardInput();
	void mouseInput(float xPos, float yPos);
};
