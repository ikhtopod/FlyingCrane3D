#pragma once

#include "Object.h"

class GridObject : public Object {
private:
	static const unsigned int DEFAULT_WIDTH;
	static const unsigned int DEFAULT_HEIGHT;
	static const unsigned int DEFAULT_STEP;

	unsigned int width;
	unsigned int height;
	unsigned int step;
public:
	GridObject(std::string _name);
	GridObject(std::string _name, unsigned int _width, unsigned int _height, unsigned int _step);
	virtual ~GridObject() = default;
};
