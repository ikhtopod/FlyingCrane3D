#include "SelectionElementPoint.h"

void SelectionElementPoint::select() {
	Application* appThis = Application::getInstancePtr();
	double xPos = 0.0;
	double yPos = 0.0;

	glfwGetCursorPos(appThis->getWindow().getWindowPtr(), &xPos, &yPos);

	this->clearColor();

	glDisable(GL_MULTISAMPLE);

	// Назначаем цвета объектам и отрисовываем
	uint32_t colorId = 0;
	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.getSelectionInfo().canSelect) continue;

		this->drawObject(objValue);

		for (auto&[meshElemKey, meshElemVertises] : objValue.getMeshElementManager().getVertices()) {
			for (auto& meshElem : meshElemVertises) {
				if (!meshElem.getSelectionInfo().canSelect) continue;

				meshElem.getSelectionInfo().colorSelect = Util::generateRGBAColorById(++colorId);

				meshElem.getSelectionInfo().isSelectionProcess = true;
				meshElem.draw();
				meshElem.getSelectionInfo().isSelectionProcess = false;
			}//rof
		}//rof
	}//rof

	glEnable(GL_MULTISAMPLE);

	// Смотрим, какой цвет под курсором мыши был у пикселя при нажатии
	GLint screenHeight = appThis->getWindow().getScreen().getHeight();
	GLubyte colorUnderCursor[4];
	glReadPixels(static_cast<int>(xPos), screenHeight - static_cast<int>(yPos),
				 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, colorUnderCursor);

	// Сохранить текущие выбранные объекты
	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.getSelectionInfo().canSelect) continue;

		for (auto&[meshElemKey, meshElemVertises] : objValue.getMeshElementManager().getVertices()) {
			for (auto& meshElem : meshElemVertises) {
				if (!meshElem.getSelectionInfo().canSelect) continue;

				if (meshElem.getSelectionInfo().colorSelectEquals(colorUnderCursor)) {
					meshElem.getSelectionInfo().isSelected = true;

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
				if (!me.getSelectionInfo().isSelected) continue;

				for (Vertex& v : me.getVertices()) {
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
