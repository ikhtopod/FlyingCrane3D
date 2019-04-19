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
			meshValue.setGlobalTransform(objValue.getParentTransform() + objValue.getTransform());
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

glm::vec3 SelectionObject::getCentroid() {
	glm::vec3 centroid { 0.0f };
	if (this->selectedObjects.empty()) return centroid;

	std::vector<glm::vec3> uniquePositions {};

	for (auto&[objKey, objValue] : this->selectedObjects) {
		for (auto&[meshKey, meshValue] : objValue->getMeshes()) {
			for (Vertex& v : meshValue.getVertices()) {
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
	Application* appThis = Application::getInstancePtr();
	double currentMouseX = 0.0;
	double currentMouseY = 0.0;

	glfwGetCursorPos(appThis->getWindow().getWindowPtr(), &currentMouseX, &currentMouseY);

	float diffMouseX = static_cast<float>(currentMouseX) - prevMousePosition.x;
	float diffMouseY = static_cast<float>(currentMouseY) - prevMousePosition.y;

	if (diffMouseX == 0.0f && diffMouseY == 0.0f) {
		return;
	}

	prevMousePosition = glm::vec2 { static_cast<float>(currentMouseX), static_cast<float>(currentMouseY) };
	diffMousePosition = glm::vec2 { diffMouseY, diffMouseX };

	Model& model = appThis->getScene().getModel();

	glm::vec3 worldCoordinate = model.getView() * glm::vec4 { diffMousePosition * 0.01f, 0.0f, 0.0f };

	for (auto&[objKey, objValue] : this->selectedObjects) {
		objValue->getTransform().setPosition(objValue->getTransform().getPosition() + worldCoordinate);

		std::cout << "x: " << worldCoordinate.x << "; "
			<< "y: " << worldCoordinate.y << "; "
			<< "z: " << worldCoordinate.z << std::endl;
	}
}

void SelectionObject::rotation() { /* dummy */ }

void SelectionObject::scaling() { /* dummy */ }
