#include "Selection.h"

const SelectionMode Selection::DEFAULT_SELECTION_MODE = SelectionMode::OBJECT;


Selection::Selection() : mode(DEFAULT_SELECTION_MODE) {}


SelectionMode Selection::getMode() {
	return this->mode;
}

void Selection::setMode(SelectionMode _mode) {
	if (this->mode != _mode) {
		this->mode = _mode;
		std::cout << (int)this->mode << std::endl;
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
