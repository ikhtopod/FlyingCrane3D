#include "DeltaTime.h"


const int DeltaTime::DEFAULT_FPS = 60;


DeltaTime::DeltaTime() : DeltaTime(DEFAULT_FPS) {}

DeltaTime::DeltaTime(unsigned int _fps)
	: fps(static_cast<float>(_fps)), duration_fps(1.0f / fps),
	deltaTime(0.0), lastTime(glfwGetTime()) {}


float DeltaTime::getFPS() {
	return this->fps;
}

void DeltaTime::setFPS(float _fps) {
	this->fps = _fps;
	this->duration_fps = 1.0f / this->fps;
}

float DeltaTime::getDurationFPS() {
	return this->duration_fps;
}


DeltaTime::operator float() {
	return this->deltaTime;
}

DeltaTime::operator std::string() {
	return std::to_string(this->deltaTime);
}


void DeltaTime::update() {
	double tmpTime = glfwGetTime();
	this->deltaTime = static_cast<float>(tmpTime - this->lastTime);
	this->lastTime = tmpTime;
}

void DeltaTime::update(bool isVSync) {
	if (!isVSync) {
		float tmpDeltaTime = static_cast<float>(glfwGetTime() - this->lastTime);

		float dur = this->duration_fps - tmpDeltaTime;
		if (dur > 0) {
			auto sleep_time = std::chrono::milliseconds(static_cast<long long>(dur * 1000));
			std::this_thread::sleep_for(sleep_time);
		}
	}

	this->update();
}
