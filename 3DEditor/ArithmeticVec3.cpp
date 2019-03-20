#include "ArithmeticVec3.h"


ArithmeticVec3::ArithmeticVec3() : ArithmeticVec3(glm::vec3 { 0.0f }) {}

ArithmeticVec3::ArithmeticVec3(glm::vec3 _value) : value(_value) {}


glm::vec3 ArithmeticVec3::getValue() const {
	return this->value;
}

void ArithmeticVec3::setValue(const glm::vec3& _value) {
	this->value = _value;
}


void ArithmeticVec3::add(const glm::vec3& _value) {
	this->setValue(this->getValue() + _value);
}

void ArithmeticVec3::sub(const glm::vec3& _value) {
	this->setValue(this->getValue() - _value);
}

void ArithmeticVec3::mul(const glm::vec3& _value) {
	this->setValue(this->getValue() * _value);
}

void ArithmeticVec3::div(const glm::vec3& _value) {
	this->setValue(this->getValue() / _value);
}


void ArithmeticVec3::add(ArithmeticVec3& _value) {
	this->add(_value.getValue());
}

void ArithmeticVec3::sub(ArithmeticVec3& _value) {
	this->sub(_value.getValue());
}

void ArithmeticVec3::mul(ArithmeticVec3& _value) {
	this->mul(_value.getValue());
}

void ArithmeticVec3::div(ArithmeticVec3& _value) {
	this->div(_value.getValue());
}
