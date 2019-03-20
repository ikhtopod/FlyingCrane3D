#include "Transform.h"


Transform::Transform(const Transform& transform) {
	this->position.setValue(transform.position.getValue());
	this->rotation.setValue(transform.rotation.getValue());
	this->scale.setValue(transform.scale.getValue());
}


Position& Transform::getPosition() {
	return this->position;
}

Rotation& Transform::getRotation() {
	return this->rotation;
}

Scale& Transform::getScale() {
	return this->scale;
}

glm::mat4 Transform::getMatrix() {
	glm::mat4 matrix = Util::IDENTITY_MATRIX;
	matrix = glm::translate(matrix, this->position.getValue());

	glm::vec3 rot = this->rotation.getValue();
	matrix = glm::rotate(matrix, glm::radians(rot.x), Axis::RIGHT);
	matrix = glm::rotate(matrix, glm::radians(rot.y), Axis::UP);
	matrix = glm::rotate(matrix, glm::radians(rot.z), Axis::FRONT);

	matrix = glm::scale(matrix, this->scale.getValue());

	return matrix;
}

