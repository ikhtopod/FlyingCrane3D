#include "ScreenResolution.h"


const int ScreenResolution::DEFAULT_SCREEN_WIDTH = 800;
const int ScreenResolution::DEFAULT_SCREEN_HEIGHT = 600;


ScreenResolution::ScreenResolution()
	: ScreenResolution(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT) {}

ScreenResolution::ScreenResolution(int sWidth, int sHeight)
	: width(sWidth), height(sHeight),
	halfWidth(sWidth / 2.0), halfHeight(sHeight / 2.0) {}


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
	this->width = _width;
	this->halfWidth = _width / 2.0;
}

void ScreenResolution::setHeight(int _height) {
	this->height = _height;
	this->halfHeight = _height / 2.0;
}


void ScreenResolution::setWidthHeight(int _width, int _height) {
	this->setWidth(_width);
	this->setHeight(_height);
}
