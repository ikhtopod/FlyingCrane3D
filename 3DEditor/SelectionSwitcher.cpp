#include "SelectionSwitcher.h"


const SelectionMode SelectionSwitcher::DEFAULT_SELECTION_MODE = SelectionMode::OBJECT;


SelectionSwitcher::SelectionSwitcher() : mode(DEFAULT_SELECTION_MODE) {
	selections.insert({ SelectionMode::POINT, std::make_shared<SelectionPoint>() });
	selections.insert({ SelectionMode::EDGE, std::make_shared<SelectionEdge>() });
	selections.insert({ SelectionMode::FACE, std::make_shared<SelectionFace>() });
	selections.insert({ SelectionMode::OBJECT, std::make_shared<SelectionObject>() });
}

SelectionMode SelectionSwitcher::getMode() {
	return this->mode;
}

void SelectionSwitcher::setMode(SelectionMode _mode) {
	if (this->mode == _mode || !this->hasSelection(_mode)) return;
	
	this->getSelection()->clearSelectedObjects();
	this->mode = _mode;

}

bool SelectionSwitcher::hasSelection(SelectionMode _mode) {
	return this->selections.find(_mode) != this->selections.end();
}

std::shared_ptr<Selection> SelectionSwitcher::getSelection() {
	return this->selections[this->mode];
}

void SelectionSwitcher::switchSelectionInput() {
	GLFWwindow* window = Application::getInstancePtr()->getWindow().getWindowPtr();

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		this->setMode(SelectionMode::POINT);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		this->setMode(SelectionMode::EDGE);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		this->setMode(SelectionMode::FACE);
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		this->setMode(SelectionMode::OBJECT);
}

void SelectionSwitcher::init() {
	for (auto& sel : this->selections) {
		sel.second->init();
	}
}

void SelectionSwitcher::draw() {
	this->getSelection()->draw();
}

void SelectionSwitcher::free() {
	for (auto& sel : this->selections) {
		sel.second->free();
	}
}
