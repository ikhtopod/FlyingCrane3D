#include "Camera.h"


const float Camera::DEFAULT_MOUSE_PITCH = 0.0f;
const float Camera::MAX_MOUSE_PITCH = 89.0f;
const float Camera::MIN_MOUSE_PITCH = -MAX_MOUSE_PITCH;

const float Camera::DEFAULT_MOUSE_YAW = -90.0f;
const float Camera::MIN_MOUSE_YAW = 0.0f;
const float Camera::MAX_MOUSE_YAW = 360.0f;

const float Camera::DEFAULT_MOUSE_ROLL = 0.0f;

const float Camera::DEFAULT_SPEED_MOVEMENT = 2.5f;
const float Camera::DEFAULT_MOUSE_SENSITIVITY_X = 0.12f;
const float Camera::DEFAULT_MOUSE_SENSITIVITY_Y = 0.1f;

const float Camera::DEFAULT_CAMERA_FOV = 45.0f;
const float Camera::MIN_CAMERA_FOV = 1.0f;
const float Camera::MAX_CAMERA_FOV = 120.0f;

const glm::vec3 Camera::DEFAULT_CAMERA_POSITION = glm::vec3 { 0.0f, 1.0f, 4.0f };


void Camera::updateCameraVectors() {
	glm::vec3 front_tmp {};

	glm::vec3 _rotation = this->transform.getRotation();

	front_tmp.x = std::cos(glm::radians(_rotation.y)) * std::cos(glm::radians(_rotation.x));
	front_tmp.y = std::sin(glm::radians(_rotation.x));
	front_tmp.z = std::sin(glm::radians(_rotation.y)) * std::cos(glm::radians(_rotation.x));

	this->axis.setFront(glm::normalize(front_tmp));

	this->axis.setRight(glm::normalize(glm::cross(this->axis.getFront(), Axis::UP)));
	this->axis.setUp(glm::normalize(glm::cross(this->axis.getRight(), this->axis.getFront())));
}


Camera::Camera()
	: speedMovement(DEFAULT_SPEED_MOVEMENT), fov(DEFAULT_CAMERA_FOV),
	mouseSensitivity(DEFAULT_MOUSE_SENSITIVITY_X, DEFAULT_MOUSE_SENSITIVITY_Y) {

	this->transform.setPosition(DEFAULT_CAMERA_POSITION);

	glm::vec3 _rotation { DEFAULT_MOUSE_PITCH, DEFAULT_MOUSE_YAW, DEFAULT_MOUSE_ROLL };
	this->transform.setRotation(_rotation);

	this->updateCameraVectors();
}


Transform& Camera::getTransform() {
	return this->transform;
}

Axis& Camera::getAxis() {
	return this->axis;
}

glm::vec2 Camera::getLastMousePosition() {
	return this->lastMousePosition;
}

float Camera::getFoV() {
	return this->fov;
}

float Camera::getSpeedMovement() {
	return this->speedMovement;
}

void Camera::setTransform(const Transform& _transform) {
	this->transform = _transform;

	this->updateCameraVectors();
}

void Camera::setAxis(const Axis& _axis) {
	this->axis = _axis;

	this->updateCameraVectors();
}

void Camera::setLastMousePosition(glm::vec2 _LastMousePosition) {
	this->lastMousePosition = _LastMousePosition;
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(
		this->transform.getPosition(),
		this->transform.getPosition() + this->axis.getFront(),
		this->axis.getUp());
}

