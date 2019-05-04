#pragma once

#include "SelectionElement.h"

class SelectionElementEdge : public SelectionElement {
public:
	virtual void select() override;

	virtual std::vector<glm::vec3> getVerticesForCentroid() override;

	virtual void moving() override;
	virtual void rotation() override;
	virtual void scaling() override;
};

