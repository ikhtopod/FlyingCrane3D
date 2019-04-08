#pragma once

#include "Util.h"
#include "TargetCamera.h"

enum class ProjectionType {
	PERSPECTIVE, ORTHOGRAPHIC
};

class Projection {
private:
	ProjectionType projectionType;
	glm::vec3 scale;

public:
	Projection();
	~Projection() = default;

	ProjectionType getProjectionType();
	void setProjectionType(ProjectionType _projectionType);

	glm::vec3 getScale();
	void setScale(glm::vec3 _scale);
	void setScaleByDistance(float distance);

	glm::mat4 getMatrix();

	bool isPerspective();
	bool isOrthographic();
};
