#include "DeltaTime.h"


const unsigned int DeltaTime::DEFAULT_FPS = 60;


float DeltaTime::mcrsecToFloatCast(Mcrsec value) {
	return duration_cast<std::chrono::duration<float>>(value).count();
}

void DeltaTime::updateDurationFps() {
	this->durationFps = Mcrsec(std::micro().den / fps);
}


DeltaTime::DeltaTime() : DeltaTime(DEFAULT_FPS) {}

DeltaTime::DeltaTime(unsigned int _fps) : fps(_fps), lastTime(FpsClock::now()) {
	this->updateDurationFps();
}


unsigned int DeltaTime::getFps() {
	return this->fps;
}

void DeltaTime::setFps(unsigned int _fps) {
	this->fps = _fps;
	this->updateDurationFps();
}
float DeltaTime::getDurationFps() {
	return DeltaTime::mcrsecToFloatCast(this->durationFps);
}


DeltaTime::operator float() {
	return DeltaTime::mcrsecToFloatCast(this->deltaTime);
}

DeltaTime::operator std::string() {
	return std::to_string(DeltaTime::mcrsecToFloatCast(this->deltaTime));
}

DeltaTime::operator Mcrsec() {
	return this->deltaTime;
}


void DeltaTime::update() {
	timePointFps tmpTime = FpsClock::now();
	this->deltaTime = duration_cast<Mcrsec>(tmpTime - this->lastTime);
	this->lastTime = tmpTime;
}

void DeltaTime::update(bool isVSync) {
	if (!isVSync) {
		Mcrsec residualDeltaTime = duration_cast<Mcrsec>(FpsClock::now() - this->lastTime);

		Mcrsec residual = duration_cast<Mcrsec>(this->durationFps - residualDeltaTime);
		if (residual.count() > DeltaTime::MIN_SLEEP_FOR) {
			std::this_thread::sleep_for(residual);
		}
	}

	this->update();
}
