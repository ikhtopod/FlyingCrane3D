#include "ScreenResolution.h"


const int ScreenResolution::DEFAULT_SCREEN_WIDTH = 800;
const int ScreenResolution::DEFAULT_SCREEN_HEIGHT = 600;


ScreenResolution::ScreenResolution()
	: ScreenResolution(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT) {}

ScreenResolution::ScreenResolution(int sWidth, int sHeight) {
	this->setWidthHeight(sWidth, sHeight);
}


int ScreenResolution::getWidth() {
	return this->width;
}

int ScreenResolution::getHeight() {
	return this->height;
}

double ScreenResolution::getHalfWidth() {
	return this->halfWidth;
}

double ScreenResolution::getHalfHeight() {
	return this->halfHeight;
}


void ScreenResolution::setWidth(int _width) {
	if (_width < 0) _width = 0;

	this->width = _width;
	this->halfWidth = static_cast<double>(_width) / 2.0;
}

void ScreenResolution::setHeight(int _height) {
	if (_height < 0) _height = 0;

	this->height = _height;
	this->halfHeight = static_cast<double>(_height) / 2.0;
}


void ScreenResolution::setWidthHeight(int _width, int _height) {
	this->setWidth(_width);
	this->setHeight(_height);
}
