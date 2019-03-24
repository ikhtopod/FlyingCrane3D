#include "Transform.h"


const glm::vec3 Transform::DEFAULT_POSITION = glm::vec3 { 0.0f };
const glm::vec3 Transform::DEFAULT_ROTATION = glm::vec3 { 0.0f };
const glm::vec3 Transform::DEFAULT_SCALE = glm::vec3 { 1.0f };


Transform Transform::matrixToTransform(const glm::mat4& _matrix) {
	glm::vec3 _scale;
	glm::quat _rotation;
	glm::vec3 _translation;
	glm::vec3 _skew;
	glm::vec4 _perspective;

	glm::decompose(_matrix, _scale, _rotation, _translation, _skew, _perspective);

	return Transform { _translation, glm::degrees(glm::eulerAngles(_rotation)), _scale };
}


Transform::Transform()
	: Transform(DEFAULT_POSITION, DEFAULT_ROTATION, DEFAULT_SCALE) {}

Transform::Transform(const Transform& transform)
	: position(transform.position), rotation(transform.rotation), scale(transform.scale) {}

Transform::Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	: position(_position), rotation(_rotation), scale(_scale) {}

Transform::Transform(glm::mat4 matrix) {
	Transform t = Transform::matrixToTransform(matrix);

	this->setPosition(t.getPosition());
	this->setRotation(t.getRotation());
	this->setScale(t.getScale());
}


Transform& Transform::operator=(const Transform& t1) {
	this->setPosition(t1.getPosition());
	this->setRotation(t1.getRotation());
	this->setScale(t1.getScale());

	return *this;
}

Transform& Transform::operator+=(const Transform& t1) {
	glm::mat4 _matrix = this->getPositionMat4() * t1.getPositionMat4()
		* this->getRotationMat4() * t1.getRotationMat4()
		* this->getScaleMat4() * t1.getScaleMat4();

	Transform t = Transform::matrixToTransform(_matrix);

	this->setPosition(t.getPosition());
	this->setRotation(t.getRotation());
	this->setScale(t.getScale());

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


void Transform::setPosition(const glm::vec3& _position) {
	this->position = _position;
}

void Transform::setRotation(const glm::vec3& _rotation) {
	this->rotation = _rotation;
}

void Transform::setScale(const glm::vec3& _scale) {
	this->scale = _scale;
}


glm::mat4 Transform::getMatrix() const {
	return this->getPositionMat4() * this->getRotationMat4() * this->getScaleMat4();
}
