#pragma once

#include "Util.h"
#include "Object.h"
#include "Vertex.h"
#include "Shader.h"

class GridObject : public Object {
private:
	using _uint = unsigned int;
	using _Cuint = const _uint;
	using FsPath = std::filesystem::path;

	static GridObject::_Cuint DEFAULT_WIDTH;
	static GridObject::_Cuint DEFAULT_HEIGHT;
	static GridObject::_Cuint DEFAULT_STEP;

private:
	_uint width;
	_uint height;
	_uint step;

public:
	GridObject();
	GridObject(_uint _width, _uint _height);
	virtual ~GridObject() = default;
};
