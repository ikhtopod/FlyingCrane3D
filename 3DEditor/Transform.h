#pragma once

#include "Util.h"
#include "Axis.h"
#include "Position.h"
#include "Rotation.h"
#include "Scale.h"

class Transform final {
private:
	Position position {};
	Rotation rotation {};
	Scale scale {};

public:
	Transform() = default;
	Transform(const Transform& transform);
	~Transform() = default;

	Position& getPosition();
	Rotation& getRotation();
	Scale& getScale();

	glm::mat4 getMatrix();
};
