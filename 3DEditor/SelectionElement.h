#pragma once

#include "Selection.h"

class SelectionElement : public Selection {
protected:
	void drawObject(Object& object);
	void drawObject(Object& object, glm::vec4 color);
};

