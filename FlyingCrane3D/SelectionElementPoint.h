#pragma once

#include "SelectionElement.h"

class SelectionElementPoint : public SelectionElement {
protected:
	virtual void drawForSelection() override;
	virtual void saveSelectedObject(glm::vec4 colorUnderCursor) override;

	virtual std::vector<glm::vec3> getVerticesForCentroid() override;

public:
	virtual void moving() override;
	virtual void rotation() override;
	virtual void scaling() override;

	virtual void deleting() override;
};
