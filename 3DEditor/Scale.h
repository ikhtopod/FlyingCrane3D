#pragma once

#include "ArithmeticVec3.h"

class Scale final : public ArithmeticVec3 {
private:
	static const glm::vec3 DEFAULT_SCALE;
public:
	using ArithmeticVec3::ArithmeticVec3;
	
	Scale();
	virtual ~Scale();
};

