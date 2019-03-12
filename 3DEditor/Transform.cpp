#include "Transform.h"


Transform::Transform() {}

Transform::~Transform() {}


Position& Transform::getPosition() {
	return this->position;
}

Rotation& Transform::getRotation() {
	return this->rotation;
}

Scale& Transform::getScale() {
	return this->scale;
}

