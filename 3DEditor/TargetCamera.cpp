#include "TargetCamera.h"

const float TargetCamera::DEFAULT_DISTANCE = 4.0f;
const float TargetCamera::MIN_DISTANCE = 1.0f;
const float TargetCamera::MAX_DISTANCE = 20.0f;
const float TargetCamera::STEP_DISTANCE = 0.2f;


TargetCamera::TargetCamera()
	: Camera(), distance(TargetCamera::DEFAULT_DISTANCE) {

	targetTransform = this->transform.getPosition() - this->axis.getFront() * distance;
}


void TargetCamera::keyboardInput() {}

void TargetCamera::mouseInput(float xPos, float yPos) {
	this->lastMousePosition.x = xPos;
	this->lastMousePosition.y = yPos;
}
