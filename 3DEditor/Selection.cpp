#include "Selection.h"

const SelectionMode Selection::DEFAULT_SELECTION_MODE = SelectionMode::OBJECT;


Selection::Selection() :
	mode(DEFAULT_SELECTION_MODE),
	shader(R"(..\resources\shaders\Selection.vs)", R"(..\resources\shaders\Selection.fs)") {}


SelectionMode Selection::getMode() {
	return this->mode;
}

void Selection::setMode(SelectionMode _mode) {
	if (this->mode != _mode) {
		this->mode = _mode;
		// При семене режима надо "сбросить" объекты, отмеченные как выделенные.
		this->selectedObjects.clear();
	}
}

void Selection::changeModeInput() {
	Application* appThis = Application::getInstancePtr();
	GLFWwindow* window = appThis->getWindow().getWindowPtr();

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		this->setMode(SelectionMode::POINT);
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		this->setMode(SelectionMode::EDGE);
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		this->setMode(SelectionMode::FACE);
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		this->setMode(SelectionMode::OBJECT);
}

void Selection::select(int button, int action, int mods) {
	if (button != GLFW_MOUSE_BUTTON_LEFT) return;

	static bool prevState = GLFW_RELEASE;

	if (action == GLFW_PRESS && prevState == GLFW_RELEASE) {

		switch (this->mode) {
			case SelectionMode::OBJECT:
				if (mods != GLFW_MOD_SHIFT) this->selectedObjects.clear();
				this->selectObject();
				break;
		}

		prevState = GLFW_PRESS;
	} else if (action == GLFW_RELEASE && prevState == GLFW_PRESS) {
		prevState = GLFW_RELEASE;
	}
}

void Selection::selectObject() {
	Application* appThis = Application::getInstancePtr();
	double xPos = 0.0;
	double yPos = 0.0;

	glfwGetCursorPos(appThis->getWindow().getWindowPtr(), &xPos, &yPos);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Назначаем цвета объектам и отрисовываем
	int counter = 0;
	for (auto&[objKey, objValue] : appThis->getScene().getObjects()) {
		if (!objValue.canSelect) continue;

		counter += 50;
		objValue.colorSelect = glm::vec4 { counter, 0.0f, 0.0f, 255.0f };

		for (auto&[meshKey, meshValue] : objValue.getMeshes()) {
			this->shader.setLambdaDraw([&objValue](Shader* _this) {
				_this->setVec4("colorCode", objValue.colorSelect);
			});

			Shader prevShader = meshValue.getShader();
			meshValue.setShader(this->shader);
			meshValue.setGlobalTransform(objValue.getGlobalTransform() + objValue.getTransform());
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
		if (!objValue.canSelect) continue;

		if (objValue.colorSelect.r == colorUnderCursor[0] &&
			objValue.colorSelect.g == colorUnderCursor[1] &&
			objValue.colorSelect.b == colorUnderCursor[2] &&
			objValue.colorSelect.a == colorUnderCursor[3]) {

			if (this->selectedObjects.find(objKey) == this->selectedObjects.end()) {
				this->selectedObjects.insert({ objKey, &objValue });
				break;
			} else {
				if (this->selectedObjects[objKey] == nullptr) {
					this->selectedObjects.erase(objKey);
					this->selectedObjects.insert({ objKey, &objValue });
					break;
				}//fi
			}//fi
		}//fi
	}//rof
}


void Selection::init() {
	this->shader.init();
	this->shader.resetLambdaDraw();
}

void Selection::draw() { /* dummy */ }

void Selection::free() {
	this->shader.free();
	this->selectedObjects.clear();
}
