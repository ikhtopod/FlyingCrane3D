#pragma once

#include "Util.h"
#include "ITriada.h"
#include "Application.h"

class GUI : public ITriada {
private:
	glm::vec4 bgColor { .2f, .2f, .3f, 1.0f };

public:
	GUI() = default;
	~GUI() = default;

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};
