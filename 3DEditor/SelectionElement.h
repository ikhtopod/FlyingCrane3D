#pragma once

#include "Selection.h"

class SelectionElement : public Selection {
protected:
	void drawObject(Object& object);
	void drawObject(Object& object, glm::vec4 color);

	void updateMovingPoints(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition);
	void updateMovingEdges(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition);
	void updateMovingFaces(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition);

	void updateMovingElements(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition);
	void updateMovingMeshes(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition);

	void updateMovingData(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition);
};

