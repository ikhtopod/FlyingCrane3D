#include "TargetCamera.h"

const float TargetCamera::DEFAULT_DISTANCE = 8.0f;
const float TargetCamera::MIN_DISTANCE = 1.0f;
const float TargetCamera::MAX_DISTANCE = 20.0f;
const float TargetCamera::STEP_DISTANCE = 0.5f;


TargetCamera::TargetCamera()
	: Camera(), distance(TargetCamera::DEFAULT_DISTANCE) {

	this->spin(this->lastMousePosition.x, this->lastMousePosition.y);
}


void TargetCamera::updatePosition() {
	this->transform.setPosition(this->targetPosition - this->axis.getFront() * this->distance);
}

void TargetCamera::normalizeTargetPosition() {
	this->targetPosition = this->transform.getPosition();
	this->targetPosition += this->axis.getFront() * this->distance;
}


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


void TargetCamera::move(float xPos, float yPos) {
	glm::vec3 newPos = this->transform.getPosition();
	newPos -= (this->axis.getRight() * (xPos - this->lastMousePosition.x)) * this->mouseSensitivity.x * 0.1f;
	newPos -= (this->axis.getUp() * (this->lastMousePosition.y - yPos)) * this->mouseSensitivity.y * 0.1f;
	this->transform.setPosition(newPos);


	this->normalizeTargetPosition();

	//this->updateCameraVectors();

	//this->updatePosition();
}

void TargetCamera::spin() {
	this->normalizeTargetPosition();
	this->spin(this->lastMousePosition.x, this->lastMousePosition.y);
}

void TargetCamera::spin(float xPos, float yPos) {
	glm::vec3 _rotation = this->transform.getRotation();

	_rotation.x += (this->lastMousePosition.y - yPos) * this->mouseSensitivity.x;
	_rotation.y += (xPos - this->lastMousePosition.x) * this->mouseSensitivity.y;

	_rotation.x = std::clamp<float>(_rotation.x, MIN_MOUSE_PITCH, MAX_MOUSE_PITCH);
	_rotation.y = Util::repeat(_rotation.y, MIN_MOUSE_YAW, MAX_MOUSE_YAW);

	this->transform.setRotation(_rotation);

	this->updateCameraVectors();

	this->updatePosition();
}

void TargetCamera::zoom(float xOffset, float yOffset) {
	this->distance -= STEP_DISTANCE * yOffset;
	this->distance = std::clamp<float>(this->distance, MIN_DISTANCE, MAX_DISTANCE);

	this->updatePosition();
}


void TargetCamera::keyboardInput() {
	int lState = glfwGetKey(Application::getInstancePtr()->getWindow().getWindowPtr(), GLFW_KEY_LEFT_SHIFT);
	int rState = glfwGetKey(Application::getInstancePtr()->getWindow().getWindowPtr(), GLFW_KEY_RIGHT_SHIFT);

	if (lState == GLFW_PRESS || rState == GLFW_PRESS) {
		this->keyShiftPressed = true;
	} else {
		this->keyShiftPressed = false;
	}
}

void TargetCamera::mouseButtonInput(int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
		this->middleMousePressed = true;

		glfwSetInputMode(Application::getInstancePtr()->getWindow().getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (mods == GLFW_MOD_SHIFT) {
			this->keyShiftPressed = true;
		} else {
			this->keyShiftPressed = false;
		}
	} else {
		this->middleMousePressed = false;
		glfwSetInputMode(Application::getInstancePtr()->getWindow().getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void TargetCamera::mouseInput(float xPos, float yPos) {
	if (this->lastMousePosition.x == xPos && this->lastMousePosition.y == yPos) return;

	if (this->middleMousePressed) {
		if (this->keyShiftPressed) {
			this->move(xPos, yPos);
		} else {
			this->spin(xPos, yPos);
		}
	}

	this->setLastMousePosition({ xPos, yPos });
}

void TargetCamera::mouseScrollInput(float xOffset, float yOffset) {
	if (!this->middleMousePressed) {
		this->zoom(xOffset, yOffset);
	}
}
