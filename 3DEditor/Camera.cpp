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

float Camera::getFoV() {
	return this->fov;
}

float Camera::getSpeedMovement() {
	return this->speedMovement;
}


glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(
		this->transform.getPosition(),
		this->transform.getPosition() + this->axis.getFront(),
		this->axis.getUp());
}

void Camera::keyboardInput() {
	Application* appThis = Application::getInstancePtr();
	GLFWwindow* window = appThis->getWindow().getWindowPtr();
	DeltaTime& delta = appThis->getDeltaTime();
	
	float velocity = this->speedMovement * delta;

	glm::vec3 pos = this->transform.getPosition();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos += this->axis.getFront() * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos += this->axis.getRight() * velocity;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		pos += this->axis.getUp() * velocity;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos -= this->axis.getFront() * velocity;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos -= this->axis.getRight() * velocity;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		pos -= this->axis.getUp() * velocity;

	this->transform.setPosition(pos);
}


void Camera::mouseInput(float xPos, float yPos) {
	static glm::vec2 lastMousePosition { xPos, yPos };

	glm::vec3 _rotation = this->transform.getRotation();

	_rotation.x += (lastMousePosition.y - yPos) * this->mouseSensitivity.x;
	_rotation.y += (xPos - lastMousePosition.x) * this->mouseSensitivity.y;

	lastMousePosition = glm::vec2 { xPos, yPos };

	_rotation.x = std::clamp<float>(_rotation.x, MIN_MOUSE_PITCH, MAX_MOUSE_PITCH);
	_rotation.y = Util::repeat(_rotation.y, MIN_MOUSE_YAW, MAX_MOUSE_YAW);

	this->transform.setRotation(_rotation);

	this->updateCameraVectors();
}
