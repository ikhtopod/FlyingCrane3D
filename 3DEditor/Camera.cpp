#include "Camera.h"


const float Camera::DEFAULT_MOUSE_PITCH = 0.0f;
const float Camera::MAX_MOUSE_PITCH = 90.0f;
const float Camera::MIN_MOUSE_PITCH = -MAX_MOUSE_PITCH;

const float Camera::DEFAULT_MOUSE_YAW = -90.0f;
const float Camera::DEFAULT_MOUSE_ROLL = 0.0f;

const float Camera::DEFAULT_SPEED_MOVEMENT = 2.5f;
const float Camera::DEFAULT_MOUSE_SENSITIVITY = 0.1f;

const float Camera::DEFAULT_CAMERA_FOV = 45.0f;
const float Camera::MIN_CAMERA_FOV = 1.0f;
const float Camera::MAX_CAMERA_FOV = 120.0f;

const glm::vec3 Camera::DEFAULT_CAMERA_POSITION = glm::vec3 { 0.0f, 0.0f, 3.0f };


void Camera::updateCameraVectors() {
	glm::vec3 front_tmp {};

	glm::vec3 _rotation = this->transform.getRotation().getValue();

	front_tmp.x = std::cos(glm::radians(_rotation.y)) * std::cos(glm::radians(_rotation.x));
	front_tmp.y = std::sin(glm::radians(_rotation.x));
	front_tmp.z = std::sin(glm::radians(_rotation.y)) * std::cos(glm::radians(_rotation.x));

	this->axis.setFront(glm::normalize(front_tmp));

	this->axis.setRight(glm::normalize(glm::cross(this->axis.getFront(), Axis::UP)));
	this->axis.setUp(glm::normalize(glm::cross(this->axis.getRight(), this->axis.getFront())));
}


Camera::Camera()
	: speedMovement(DEFAULT_SPEED_MOVEMENT),
	mouseSensitivity(DEFAULT_MOUSE_SENSITIVITY),
	fov(DEFAULT_CAMERA_FOV) {

	this->transform.getPosition().setValue(DEFAULT_CAMERA_POSITION);

	glm::vec3 _rotation { DEFAULT_MOUSE_PITCH, DEFAULT_MOUSE_YAW, DEFAULT_MOUSE_ROLL };
	this->transform.getRotation().setValue(_rotation);

	this->updateCameraVectors();
}

Camera::~Camera() {}


float Camera::getFoV() {
	return this->fov;
}

float Camera::getSpeedMovement() {
	return this->speedMovement;
}


glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(
		this->transform.getPosition().getValue(),
		this->transform.getPosition().getValue() + this->axis.getFront(),
		this->axis.getUp());
}

void Camera::keyboardMovement(CameraMovement direction, float deltaTime) {
	float velocity = this->speedMovement * deltaTime;

	if (direction == CameraMovement::FORWARD)
		this->transform.getPosition().add(this->axis.getFront() * velocity);
	if (direction == CameraMovement::BACKWARD)
		this->transform.getPosition().sub(this->axis.getFront() * velocity);
	if (direction == CameraMovement::RIGHT)
		this->transform.getPosition().add(this->axis.getRight() * velocity);
	if (direction == CameraMovement::LEFT)
		this->transform.getPosition().sub(this->axis.getRight() * velocity);
	if (direction == CameraMovement::UP)
		this->transform.getPosition().add(this->axis.getUp() * velocity);
	if (direction == CameraMovement::DOWN)
		this->transform.getPosition().sub(this->axis.getUp() * velocity);
}

void Camera::mouseMovement(float xOffset, float yOffset) {
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;

	glm::vec3 _rotation = this->transform.getRotation().getValue();

	_rotation.y += xOffset;
	_rotation.x += yOffset;
	_rotation.x = std::clamp<float>(_rotation.x, MIN_MOUSE_PITCH, MAX_MOUSE_PITCH);

	this->transform.getRotation().setValue(_rotation);

	this->updateCameraVectors();
}
