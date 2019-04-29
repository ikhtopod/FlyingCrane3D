#include "SelectionObject.h"


void SelectionObject::select() {
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

		objValue.getSelectionInfo().colorSelect = Util::generateRGBAColorById(++colorId);

		for (auto&[meshKey, meshValue] : objValue.getMeshes()) {
			this->shader.setLambdaDraw([&objValue](Shader* _this) {
				_this->setVec4("colorCode", objValue.getSelectionInfo().colorSelect);
			});

			Shader prevShader = meshValue.getShader();
			meshValue.setShader(this->shader);
			meshValue.setGlobalTransform(objValue.getParentTransform() + objValue.getTransform());
			meshValue.draw();
			meshValue.setShader(prevShader);
		}//rof
	}//rof

	// Смотрим, какой цвет под курсором мыши был у пикселя при нажатии
	GLint screenHeight = appThis->getWindow().getScreen().getHeight();
	GLubyte colorUnderCursor[4];
	glReadPixels(static_cast<int>(xPos), screenHeight - static_cast<int>(yPos), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, colorUnderCursor);

	// Сохранить текущие выбранные объекты
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

glm::vec3 SelectionObject::getCentroid() {
	glm::vec3 centroid { 0.0f };
	if (this->selectedObjects.empty()) return centroid;

	std::vector<glm::vec3> uniquePositions {};

	for (auto&[objKey, objValue] : this->selectedObjects) {
		for (auto&[meshKey, meshValue] : objValue->getMeshes()) {
			for (Vertex& v : meshValue.getPolymesh().getVertices()) {
				glm::vec3 pos = v.position + objValue->getGlobalTransform().getPosition();
				uniquePositions.push_back(pos);
			}//rof
		}//rof
	}//rof

	auto sortPred = [](const glm::vec3& lhs, const glm::vec3& rhs) -> bool {
		return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z;
	};

	std::sort(uniquePositions.begin(), uniquePositions.end(), sortPred);
	uniquePositions.erase(std::unique(uniquePositions.begin(), uniquePositions.end()), uniquePositions.end());

	if (uniquePositions.size() > 1) {
		centroid = std::accumulate(std::next(uniquePositions.begin()), uniquePositions.end(),
								   uniquePositions[0], std::plus<glm::vec3>());
		centroid /= static_cast<float>(uniquePositions.size());
	} else {
		centroid = uniquePositions[0];
	}

	return centroid;
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
