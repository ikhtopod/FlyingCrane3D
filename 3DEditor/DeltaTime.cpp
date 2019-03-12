#include "DeltaTime.h"


DeltaTime::DeltaTime() : deltaTime(0.0), lastTime(glfwGetTime()) {}

DeltaTime::~DeltaTime() {}


DeltaTime::operator float() {
	return this->deltaTime;
}


void DeltaTime::update() {
	double tmpTime = glfwGetTime();
	this->deltaTime = static_cast<float>(tmpTime - this->lastTime);
	this->lastTime = tmpTime;
}
