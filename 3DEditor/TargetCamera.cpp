#include "TargetCamera.h"

const float TargetCamera::DEFAULT_DISTANCE = 6.0f;
const float TargetCamera::MIN_DISTANCE = 1.0f;
const float TargetCamera::MAX_DISTANCE = 20.0f;
const float TargetCamera::STEP_DISTANCE = 0.5f;


TargetCamera::TargetCamera()
	: Camera(),
	distance(TargetCamera::DEFAULT_DISTANCE), targetPosition(0.0f) {}


glm::vec3 TargetCamera::getTargetPosition() {
	return this->targetPosition;
}

float TargetCamera::getDistance() {
	return this->distance;
}

void TargetCamera::setTargetPosition(glm::vec3 _targetPosition) {
	this->targetPosition = _targetPosition;
}

void TargetCamera::setDistance(float _distance) {
	this->distance = _distance;
}


void TargetCamera::move() {

}

void TargetCamera::spin() {

}

void TargetCamera::zoom() {

}


void TargetCamera::keyboardInput() {
	Application* appThis = Application::getInstancePtr();
	GLFWwindow* window = appThis->getWindow().getWindowPtr();
	DeltaTime& delta = appThis->getDeltaTime();

	float velocity = this->speedMovement * delta;



}

void TargetCamera::mouseInput(float xPos, float yPos) {
	glm::vec3 _rotation = this->transform.getRotation();

	_rotation.x += (this->lastMousePosition.y - yPos) * this->mouseSensitivity.x;
	_rotation.y += (xPos - this->lastMousePosition.x) * this->mouseSensitivity.y;

	this->setLastMousePosition({ xPos, yPos });

	_rotation.x = std::clamp<float>(_rotation.x, MIN_MOUSE_PITCH, MAX_MOUSE_PITCH);
	_rotation.y = Util::repeat(_rotation.y, MIN_MOUSE_YAW, MAX_MOUSE_YAW);

	this->transform.setRotation(_rotation);

	this->updateCameraVectors();


	glm::vec3 pos = this->targetPosition;

	pos -= this->axis.getFront() * this->distance;
	pos += this->axis.getUp() * this->distance;
	pos -= this->axis.getUp() * this->distance;

	this->transform.setPosition(pos);
}

void TargetCamera::mouseButtonInput(int button, int action, int mods) {
	// mods: GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_ALT, GLFW_MOD_SUPER 
}

void TargetCamera::mouseScrollInput(float xOffset, float yOffset) {
	this->distance -= STEP_DISTANCE * yOffset;

	this->distance = std::clamp<float>(this->distance, MIN_DISTANCE, MAX_DISTANCE);

	glm::vec3 pos = this->targetPosition;

	pos -= this->axis.getFront() * this->distance;
	pos += this->axis.getUp() * this->distance;
	pos -= this->axis.getUp() * this->distance;

	this->transform.setPosition(pos);
}
