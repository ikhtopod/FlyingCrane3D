#include "Transform.h"


Transform::Transform()
	: Transform(glm::vec3 { 0.0f }, glm::vec3 { 0.0f }, glm::vec3 { 1.0f }) {}

Transform::Transform(const Transform& transform)
	: position(transform.position), rotation(transform.rotation), scale(transform.scale) {}


glm::vec3 Transform::getPosition() {
	return this->position;
}

glm::vec3 Transform::getRotation() {
	return this->rotation;
}

glm::vec3 Transform::getScale() {
	return this->scale;
}

void Transform::setPosition(glm::vec3 _position) {
	this->position = _position;
}

void Transform::setRotation(glm::vec3 _rotation) {
	this->rotation = _rotation;
}

void Transform::setScale(glm::vec3 _scale) {
	this->scale = _scale;
}


Transform::Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	: position(_position), rotation(_rotation), scale(_scale) {}



glm::mat4 Transform::getMatrix() {
	glm::mat4 matrix = Util::IDENTITY_MATRIX;
	matrix = glm::translate(matrix, this->position);

	glm::vec3 rot = this->rotation;
	matrix = glm::rotate(matrix, glm::radians(rot.x), Axis::RIGHT);
	matrix = glm::rotate(matrix, glm::radians(rot.y), Axis::UP);
	matrix = glm::rotate(matrix, glm::radians(rot.z), Axis::FRONT);

	matrix = glm::scale(matrix, this->scale);

	return matrix;
}

