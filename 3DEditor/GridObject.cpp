#include "GridObject.h"


const unsigned int GridObject::DEFAULT_WIDTH = 16;
const unsigned int GridObject::DEFAULT_HEIGHT = GridObject::DEFAULT_WIDTH;
const unsigned int GridObject::DEFAULT_STEP = 1;


GridObject::GridObject(std::string _name)
	: GridObject(_name, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_STEP) {}

GridObject::GridObject(std::string _name, unsigned int _width, unsigned int _height, unsigned int _step)
	: Object(_name), width(_width), height(_height), step(_step) {}

