#include "SelectionElement.h"


void SelectionElement::drawObject(Object& object) {
	this->drawObject(object, CLEAR_COLOR);
}

// Отрисовать объект, чтобы вершины, спрятанные за ним, не выделялись
void SelectionElement::drawObject(Object& object, glm::vec4 color) {
	object.getSelectionInfo().colorSelect = color;
	object.getSelectionInfo().isSelectionProcess = true;

	for (auto&[meshKey, meshValue] : object.getMeshes()) {
		meshValue.setGlobalTransform(object.getParentTransform() + object.getTransform());
		meshValue.draw();
	}//rof

	object.getSelectionInfo().isSelectionProcess = false;
}


void SelectionElement::
updateMovingPoints(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition) {
	for (auto&[meshName, meshElements] : object->getMeshElementManager().getPoints()) {
		for (auto& meshElement : meshElements) {
			for (Vertex& v : meshElement->getVertices()) {
				if (v.position == oldPosition) {
					v.position = newPosition;
				}//fi
			}//rof

			meshElement->updateBufferedVertices();
		}//rof
	}//rof
}

void SelectionElement::
updateMovingEdges(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition) {
	for (auto&[meshName, meshElements] : object->getMeshElementManager().getEdges()) {
		for (auto& meshElement : meshElements) {
			for (Vertex& v : meshElement->getVertices()) {
				if (v.position == oldPosition) {
					v.position = newPosition;
				}//fi
			}//rof

			meshElement->updateBufferedVertices();
		}//rof
	}//rof
}

void SelectionElement::
updateMovingFaces(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition) {
	for (auto&[meshName, meshElements] : object->getMeshElementManager().getFaces()) {
		for (auto& meshElement : meshElements) {
			for (Vertex& v : meshElement->getVertices()) {
				if (v.position == oldPosition) {
					v.position = newPosition;
				}//fi
			}//rof

			meshElement->updateBufferedVertices();
		}//rof
	}//rof
}

void SelectionElement::
updateMovingElements(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition) {
	this->updateMovingPoints(object, oldPosition, newPosition);
	this->updateMovingEdges(object, oldPosition, newPosition);
	this->updateMovingFaces(object, oldPosition, newPosition);
}

void SelectionElement::
updateMovingMeshes(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition) {
	for (auto&[meshName, mesh] : object->getMeshes()) {
		for (auto& v : mesh.getPolymesh().getVertices()) {
			if (v.position == oldPosition) {
				v.position = newPosition;
			}//fi
		}//rof

		mesh.getPolymesh().update();
		mesh.updateBufferedVertices();
	}//rof
}

void SelectionElement::
updateMovingData(Object* object, glm::vec3& oldPosition, glm::vec3& newPosition) {
	this->updateMovingElements(object, oldPosition, newPosition);
	this->updateMovingMeshes(object, oldPosition, newPosition);
}
