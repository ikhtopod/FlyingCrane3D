#pragma once

#include "Position.h"
#include "Rotation.h"
#include "Scale.h"

class Transform final {
private:
	Position position {};
	Rotation rotation {};
	Scale scale {};
public:
	Transform();
	~Transform();

	Position& getPosition();
	Rotation& getRotation();
	Scale& getScale();
};
