#include "SelectionPoint.h"

void SelectionPoint::select() {
	Application* appThis = Application::getInstancePtr();
	double xPos = 0.0;
	double yPos = 0.0;

	glfwGetCursorPos(appThis->getWindow().getWindowPtr(), &xPos, &yPos);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Назначаем цвета объектам и отрисовываем
	uint32_t colorId = 0;
	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.getSelectionInfo().canSelect) continue;

		// Отрисовать объект, чтобы вершины, спрятанные за ним, не выделялись
		for (auto&[meshKey, meshValue] : objValue.getMeshes()) {
			this->shader.setLambdaDraw([&objValue](Shader* _this) {
				_this->setVec4("colorCode", glm::vec4 { 0.0f, 0.0f, 0.0f, 0.0f });
			});

			Shader prevShader = meshValue.getShader();
			meshValue.setShader(this->shader);
			meshValue.setGlobalTransform(objValue.getParentTransform() + objValue.getTransform());
			meshValue.draw();
			meshValue.setShader(prevShader);
		}//rof

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

glm::vec3 SelectionPoint::getCentroid() {
	return glm::vec3 {};
}

void SelectionPoint::moving() { /* dummy */ }

void SelectionPoint::rotation() { /* dummy */ }

void SelectionPoint::scaling() { /* dummy */ }
