#pragma once

#include "Selection.h"

class SelectionElement : public Selection {
private:
	using SharedObject = std::shared_ptr<Object>;

private:
	void updateMovingPoints(const SharedObject& object, glm::vec3& oldPosition, glm::vec3& newPosition);
	void updateMovingEdges(const SharedObject& object, glm::vec3& oldPosition, glm::vec3& newPosition);
	void updateMovingFaces(const SharedObject& object, glm::vec3& oldPosition, glm::vec3& newPosition);

	void updateMovingElements(const SharedObject& object, glm::vec3& oldPosition, glm::vec3& newPosition);
	void updateMovingMeshes(const SharedObject& object, glm::vec3& oldPosition, glm::vec3& newPosition);

protected:
	void drawObject(const SharedObject& object);
	void drawObject(const SharedObject& object, glm::vec4 color);

	void updateMovingData(const SharedObject& object, glm::vec3& oldPosition, glm::vec3& newPosition);
};

