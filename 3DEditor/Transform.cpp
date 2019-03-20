#include "Transform.h"


Transform::Transform()
	: Transform(glm::vec3 { 0.0f }, glm::vec3 { 0.0f }, glm::vec3 { 1.0f }) {}

Transform::Transform(const Transform& transform)
	: position(transform.position), rotation(transform.rotation), scale(transform.scale) {}

Transform::Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	: position(_position), rotation(_rotation), scale(_scale) {}


Transform& Transform::operator+=(const Transform& t1) {
	glm::vec3 _scale;
	glm::quat _rotation;
	glm::vec3 _translation;
	glm::vec3 _skew;
	glm::vec4 _perspective;

	glm::mat4 _matrix = t1.getMatrix() * this->getMatrix();

	glm::decompose(_matrix, _scale, _rotation, _translation, _skew, _perspective);

	this->setPosition(_translation);
	this->setRotation(glm::degrees(glm::eulerAngles(glm::conjugate(_rotation))));
	this->setScale(_scale);

	return *this;
}

Transform operator+(Transform t1, const Transform& t2) {
	t1 += t2;
	return t1;
}


glm::vec3 Transform::getPosition() const {
	return this->position;
}

glm::vec3 Transform::getRotation() const {
	return this->rotation;
}

glm::vec3 Transform::getScale() const {
	return this->scale;
}

glm::mat4 Transform::getPositionMat4() const {
	return glm::translate(this->position);
}

glm::mat4 Transform::getRotationMat4() const {
	glm::mat4 rotationX = glm::rotate(glm::radians(this->rotation.x), Axis::RIGHT);
	glm::mat4 rotationY = glm::rotate(glm::radians(this->rotation.y), Axis::UP);
	glm::mat4 rotationZ = glm::rotate(glm::radians(this->rotation.z), Axis::FRONT);

	return rotationX * rotationY * rotationZ;
}

glm::mat4 Transform::getScaleMat4() const {
	return glm::scale(this->scale);
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


glm::mat4 Transform::getMatrix() const {
	return this->getPositionMat4() * this->getRotationMat4() * this->getScaleMat4();
}
