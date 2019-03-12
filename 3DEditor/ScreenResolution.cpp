#include "ScreenResolution.h"


const int ScreenResolution::DEFAULT_SCREEN_WIDTH = 800;
const int ScreenResolution::DEFAULT_SCREEN_HEIGHT = 600;


ScreenResolution::ScreenResolution()
	: ScreenResolution(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT) {}

ScreenResolution::ScreenResolution(int sWidth, int sHeight)
	: width(sWidth), height(sHeight) {}


ScreenResolution::~ScreenResolution() {}


int ScreenResolution::getWidth() {
	return this->width;
}

void ScreenResolution::setWidth(int _width) {
	this->width = _width;
}


int ScreenResolution::getHeight() {
	return this->height;
}

void ScreenResolution::setHeight(int _height) {
	this->height = _height;
}


void ScreenResolution::setWidthHeight(int _width, int _height) {
	this->setWidth(_width);
	this->setHeight(_height);
}
