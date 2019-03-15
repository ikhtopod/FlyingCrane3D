#pragma once

#include "Util.h"
#include "Object.h"
#include "Vertex.h"
#include "Shader.h"

class GridObject : public Object {
private:
	static const unsigned int DEFAULT_WIDTH;
	static const unsigned int DEFAULT_HEIGHT;
	static const unsigned int DEFAULT_STEP;

	unsigned int width;
	unsigned int height;
	unsigned int step;
public:
	GridObject();
	GridObject(unsigned int _width, unsigned int _height, unsigned int _step);
	virtual ~GridObject() = default;
};
