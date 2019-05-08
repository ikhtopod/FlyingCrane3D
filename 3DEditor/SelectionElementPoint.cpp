#include "SelectionElementPoint.h"


void SelectionElementPoint::drawForSelection() {
	Application* appThis = Application::getInstancePtr();

	uint32_t colorId = 0;
	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.getSelectionInfo().canSelect) continue;

		for (auto&[meshName, meshElements] : objValue.getMeshElementManager().getPoints()) {
			for (auto& meshElement : meshElements) {
				if (!meshElement->getSelectionInfo().canSelect) continue;

				meshElement->getSelectionInfo().colorSelect = Util::generateRGBAColorById(++colorId);

				meshElement->getSelectionInfo().isSelectionProcess = true;
				meshElement->draw();
				meshElement->getSelectionInfo().isSelectionProcess = false;
			}//rof
		}//rof

		this->drawObject(objValue);
	}//rof
}

void SelectionElementPoint::saveSelectedObject(glm::vec4 colorUnderCursor) {
	Application* appThis = Application::getInstancePtr();

	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.getSelectionInfo().canSelect) continue;

		for (auto&[meshName, meshElements] : objValue.getMeshElementManager().getPoints()) {
			for (auto& meshElement : meshElements) {
				if (!meshElement->getSelectionInfo().canSelect) continue;

				if (meshElement->getSelectionInfo().colorSelectEquals(colorUnderCursor)) {
					meshElement->getSelectionInfo().isSelected = true;

					if (this->hasSelectedObject(objKey)) {
						if (this->selectedObjects[objKey] == nullptr) {
							this->selectedObjects.erase(objKey);
							this->selectedObjects.insert({ objKey, &objValue });
							break;
						}//fi
					} else {
						this->selectedObjects.insert({ objKey, &objValue });
						break;
					}//fi
				}//fi

				meshElement->getSelectionInfo().colorSelect = CLEAR_COLOR;
			}//rof
		}//rof
	}//rof
}

std::vector<glm::vec3> SelectionElementPoint::getVerticesForCentroid() {
	std::vector<glm::vec3> centroidVertices {};

	for (auto&[objName, objValue] : this->selectedObjects) {
		for (auto&[meshName, meshElements] : objValue->getMeshElementManager().getPoints()) {
			for (auto& me : meshElements) {
				if (!me->getSelectionInfo().isSelected) continue;

				for (Vertex& v : me->getVertices()) {
					glm::vec3 pos = v.position + objValue->getGlobalTransform().getPosition();
					centroidVertices.push_back(pos);
				}//rof
			}//rof
		}//rof
	}//rof

	return centroidVertices;
}

void SelectionElementPoint::moving() {
	this->updateMousePosition();

	if (this->diffIsZero()) return;

	Application* appThis = Application::getInstancePtr();

	Axis& cameraAxis = appThis->getScene().getCamera().getAxis();
	float deltaTime = appThis->getDeltaTime();

	for (auto&[objName, objValue] : this->selectedObjects) {
		for (auto&[meshName, meshElements] : objValue->getMeshElementManager().getPoints()) {
			for (auto& me : meshElements) {
				if (!me->getSelectionInfo().isSelected) continue;

				for (Vertex& v : me->getVertices()) {
					v.position += (cameraAxis.getRight() * diffMousePosition.x) * deltaTime;
					v.position += (cameraAxis.getUp() * diffMousePosition.y) * deltaTime;
				}//rof

				me->updateBufferedVertices();
			}//rof
		}//rof
	}//rof
}

void SelectionElementPoint::rotation() { /* dummy */ }

void SelectionElementPoint::scaling() { /* dummy */ }
