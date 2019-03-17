#pragma once

#include "Util.h"
#include "Transform.h"
#include "Axis.h"

enum class CameraMovement {
	FORWARD, BACKWARD,
	LEFT, RIGHT,
	UP, DOWN
};

class Camera final {
public:
	static const float DEFAULT_MOUSE_PITCH;
	static const float MIN_MOUSE_PITCH;
	static const float MAX_MOUSE_PITCH;

	static const float DEFAULT_MOUSE_YAW;
	static const float MIN_MOUSE_YAW;
	static const float MAX_MOUSE_YAW;

	static const float DEFAULT_MOUSE_ROLL;

	static const float DEFAULT_SPEED_MOVEMENT;
	static const float DEFAULT_MOUSE_SENSITIVITY;

	static const float DEFAULT_CAMERA_FOV;
	static const float MIN_CAMERA_FOV;
	static const float MAX_CAMERA_FOV;

	static const glm::vec3 DEFAULT_CAMERA_POSITION;


private:
	Transform transform {};
	Axis axis {};

	float speedMovement;
	float mouseSensitivity;
	float fov;

private:
	void updateCameraVectors();

public:
	Camera();
	~Camera() = default;

	Transform& getTransform();

	float getFoV();
	float getSpeedMovement();

	glm::mat4 GetViewMatrix();

	void keyboardMovement(CameraMovement direction, float deltaTime);
	void mouseMovement(float xOffset, float yOffset);
};
