#include "ArithmeticVec3.h"


ArithmeticVec3::ArithmeticVec3() : ArithmeticVec3(glm::vec3 { 0.0f }) {}

ArithmeticVec3::ArithmeticVec3(glm::vec3 _value) : value(_value) {}


glm::vec3 ArithmeticVec3::getValue() {
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
