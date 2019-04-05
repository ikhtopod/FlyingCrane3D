#pragma once

#include "Selection.h"

class SelectionEdge : public Selection {
	virtual void select() override;

	virtual glm::vec3 getCentroid() override;

	virtual void moving() override;
	virtual void rotation() override;
	virtual void scaling() override;
};

