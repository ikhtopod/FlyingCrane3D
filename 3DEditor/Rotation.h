#pragma once

#include "ArithmeticVec3.h"

class Rotation final : public ArithmeticVec3 {
public:
	using ArithmeticVec3::ArithmeticVec3;

	virtual ~Rotation();
};
