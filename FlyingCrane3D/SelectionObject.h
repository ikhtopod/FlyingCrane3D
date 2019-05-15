#pragma once

#include "Util.h"
#include "Selection.h"
#include "Application.h"
#include "Vertex.h"
#include "Shader.h"
#include "SelectionInfo.h"
#include "Axis.h"

class SelectionObject : public Selection {
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
