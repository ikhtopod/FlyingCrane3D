#include "SelectionElementPoint.h"


void SelectionElementPoint::select() {
	Application* appThis = Application::getInstancePtr();

	Util::clearColor(Selection::CLEAR_COLOR);

	glDisable(GL_MULTISAMPLE);

	// Назначаем цвета объектам и отрисовываем
	uint32_t colorId = 0;
	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.getSelectionInfo().canSelect) continue;

		for (auto&[meshElemKey, meshElements] : objValue.getMeshElementManager().getVertices()) {
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

	glEnable(GL_MULTISAMPLE);

	glm::vec4 colorUnderCursor = Selection::getColorUnderCursor();

	// Сохранить текущие выбранные объекты
	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.getSelectionInfo().canSelect) continue;

		for (auto&[meshElemKey, meshElements] : objValue.getMeshElementManager().getVertices()) {
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
			}//rof
		}//rof
	}//rof
}

std::vector<glm::vec3> SelectionElementPoint::getVerticesForCentroid() {
	std::vector<glm::vec3> centroidVertices {};

	for (auto&[objName, objValue] : this->selectedObjects) {
		for (auto&[meshName, meshElements] : objValue->getMeshElementManager().getVertices()) {
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

void SelectionElementPoint::moving() { /* dummy */ }

void SelectionElementPoint::rotation() { /* dummy */ }

void SelectionElementPoint::scaling() { /* dummy */ }
