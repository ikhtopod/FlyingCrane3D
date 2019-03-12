#pragma once

#include "ArithmeticVec3.h"

class Position final : public ArithmeticVec3 {
public:
	using ArithmeticVec3::ArithmeticVec3;

	virtual ~Position();
};
