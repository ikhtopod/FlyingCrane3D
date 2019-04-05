#include "SelectionObject.h"


void SelectionObject::select() {
	Application* appThis = Application::getInstancePtr();
	double xPos = 0.0;
	double yPos = 0.0;

	glfwGetCursorPos(appThis->getWindow().getWindowPtr(), &xPos, &yPos);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ��������� ����� �������� � ������������
	uint32_t colorId = 0;
	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.getSelectionInfo().canSelect) continue;

		objValue.getSelectionInfo().colorSelect = Util::generateRGBAColorById(++colorId);

		for (auto&[meshKey, meshValue] : objValue.getMeshes()) {
			this->shader.setLambdaDraw([&objValue](Shader* _this) {
				_this->setVec4("colorCode", objValue.getSelectionInfo().colorSelect);
			});

			Shader prevShader = meshValue.getShader();
			meshValue.setShader(this->shader);
			meshValue.setGlobalTransform(objValue.getGlobalTransform() + objValue.getTransform());
			meshValue.draw();
			meshValue.setShader(prevShader);
		}//rof
	}//rof

	// �������, ����� ���� ��� �������� ���� ��� � ������� ��� �������
	GLint screenHeight = appThis->getWindow().getScreen().getHeight();
	GLubyte colorUnderCursor[4];
	glReadPixels(static_cast<int>(xPos), screenHeight - static_cast<int>(yPos), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, colorUnderCursor);

	// ��������� ������� ��������� �������
	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.getSelectionInfo().canSelect) continue;

		if (objValue.getSelectionInfo().colorSelectEquals(colorUnderCursor)) {
			if (this->hasSelectedObjects(objKey)) {
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
}

void SelectionObject::moving() {
	Application* appThis = Application::getInstancePtr();
	double xPos = 0.0;
	double yPos = 0.0;

	glfwGetCursorPos(appThis->getWindow().getWindowPtr(), &xPos, &yPos);

	for (auto&[objKey, objValue] : this->selectedObjects) {
		// set transform selected object
	}
}

void SelectionObject::rotation() { /* dummy */ }

void SelectionObject::scaling() { /* dummy */ }

