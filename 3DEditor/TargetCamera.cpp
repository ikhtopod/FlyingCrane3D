#include "TargetCamera.h"

const float TargetCamera::DEFAULT_DISTANCE = 6.0f;
const float TargetCamera::MIN_DISTANCE = 1.0f;
const float TargetCamera::MAX_DISTANCE = 20.0f;
const float TargetCamera::STEP_DISTANCE = 0.2f;


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



	this->updateCameraVectors();
}

void TargetCamera::spin() {



	this->updateCameraVectors();
}

void TargetCamera::zoom() {



	this->updateCameraVectors();
}


void TargetCamera::keyboardInput() {
	Application* appThis = Application::getInstancePtr();
	GLFWwindow* window = appThis->getWindow().getWindowPtr();
	DeltaTime& delta = appThis->getDeltaTime();

	float velocity = this->speedMovement * delta;



	this->updateCameraVectors();
}

void TargetCamera::mouseInput(float xPos, float yPos) {


	this->setLastMousePosition({ xPos, yPos });

	this->updateCameraVectors();
}
