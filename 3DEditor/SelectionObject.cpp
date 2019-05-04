#include "SelectionObject.h"


void SelectionObject::select() {
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

		objValue.getSelectionInfo().colorSelect = Util::generateRGBAColorById(++colorId);
		objValue.getSelectionInfo().isSelectionProcess = true;

		for (auto&[meshKey, meshValue] : objValue.getMeshes()) {
			meshValue.setGlobalTransform(objValue.getParentTransform() + objValue.getTransform());
			meshValue.draw();
		}//rof

		objValue.getSelectionInfo().isSelectionProcess = false;
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

		if (objValue.getSelectionInfo().colorSelectEquals(colorUnderCursor)) {
			objValue.getSelectionInfo().isSelected = true;

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
}

std::vector<glm::vec3> SelectionObject::getVerticesForCentroid() {
	std::vector<glm::vec3> centroidVertices {};

	for (auto&[objName, objValue] : this->selectedObjects) {
		for (auto&[meshName, meshValue] : objValue->getMeshes()) {
			for (Vertex& v : meshValue.getPolymesh().getVertices()) {
				glm::vec3 pos = v.position + objValue->getGlobalTransform().getPosition();
				centroidVertices.push_back(pos);
			}//rof
		}//rof
	}//rof

	return centroidVertices;
}

void SelectionObject::moving() {
	this->updateMousePosition();

	if (this->diffIsZero()) return;

	Application* appThis = Application::getInstancePtr();

	Axis& cameraAxis = appThis->getScene().getCamera().getAxis();
	float deltaTime = appThis->getDeltaTime();

	for (auto&[objKey, objValue] : this->selectedObjects) {
		glm::vec3 newPos = objValue->getTransform().getPosition();
		newPos += (cameraAxis.getRight() * diffMousePosition.x) * deltaTime;
		newPos += (cameraAxis.getUp() * diffMousePosition.y) * deltaTime;
		objValue->getTransform().setPosition(newPos);
	}
}

void SelectionObject::rotation() {
	const static float STEP = 10.0f;

	this->updateMousePosition();

	if (this->diffIsZero()) return;

	Application* appThis = Application::getInstancePtr();

	Axis& cameraAxis = appThis->getScene().getCamera().getAxis();
	float deltaTime = appThis->getDeltaTime();

	for (auto&[objKey, objValue] : this->selectedObjects) {
		glm::vec3 newRot = objValue->getTransform().getRotation();
		newRot -= (cameraAxis.getRight() * diffMousePosition.y) * STEP * deltaTime;
		newRot += (cameraAxis.getUp() * diffMousePosition.x) * STEP * deltaTime;
		objValue->getTransform().setRotation(newRot);
	}
}

void SelectionObject::scaling() {
	this->updateMousePosition();

	if (this->diffIsZero()) return;

	float deltaTime = Application::getInstancePtr()->getDeltaTime();

	for (auto&[objKey, objValue] : this->selectedObjects) {
		glm::vec3 newScale = objValue->getTransform().getScale();
		newScale += ((diffMousePosition.x + diffMousePosition.y) / 2.0f) * deltaTime;
		objValue->getTransform().setScale(newScale);
	}
}
