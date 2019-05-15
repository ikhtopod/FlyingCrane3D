#pragma once

#include "Util.h"
#include "ObjectScene.h"
#include "Vertex.h"
#include "Shader.h"
#include "PolymeshRepresentation.h"

class ObjectSceneGrid final : public ObjectScene {
private:
	using _uint = unsigned int;
	using _Cuint = const _uint;
	using FsPath = std::filesystem::path;

	static ObjectSceneGrid::_Cuint DEFAULT_WIDTH;
	static ObjectSceneGrid::_Cuint DEFAULT_HEIGHT;
	static ObjectSceneGrid::_Cuint DEFAULT_STEP;

private:
	_uint width;
	_uint height;
	_uint step;

public:
	ObjectSceneGrid();
	ObjectSceneGrid(_uint _width, _uint _height);
	virtual ~ObjectSceneGrid() = default;
};
