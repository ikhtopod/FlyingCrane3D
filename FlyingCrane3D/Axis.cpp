#include "Axis.h"


const glm::vec3 Axis::X = glm::vec3 { 1.0f, 0.0f, 0.0f };
const glm::vec3 Axis::Y = glm::vec3 { 0.0f, 1.0f, 0.0f };
const glm::vec3 Axis::Z = glm::vec3 { 0.0f, 0.0f, 1.0f };

const glm::vec3 Axis::RIGHT = Axis::X;
const glm::vec3 Axis::PITCH = Axis::X;

const glm::vec3 Axis::UP = Axis::Y;
const glm::vec3 Axis::YAW = Axis::Y;

const glm::vec3 Axis::FORWARD = Axis::Z;
const glm::vec3 Axis::FRONT = Axis::Z;
const glm::vec3 Axis::ROLL = Axis::Z;


const glm::vec3 Axis::LEFT = -Axis::RIGHT;
const glm::vec3 Axis::DOWN = -Axis::UP;
const glm::vec3 Axis::BACK = -Axis::FRONT;
const glm::vec3 Axis::BACKWARD = -Axis::FORWARD;


Axis::Axis() : Axis(Axis::RIGHT, Axis::UP, Axis::FRONT) {}

Axis::Axis(glm::vec3 _right, glm::vec3 _up, glm::vec3 _front)
	: right(_right), up(_up), front(_front) {}


glm::vec3 Axis::getRight() const {
	return this->right;
}

glm::vec3 Axis::getUp() const {
	return this->up;
}

glm::vec3 Axis::getFront() const {
	return this->front;
}


void Axis::setRight(glm::vec3 _right) {
	this->right = _right;
}

void Axis::setUp(glm::vec3 _up) {
	this->up = _up;
}

void Axis::setFront(glm::vec3 _front) {
	this->front = _front;
}

