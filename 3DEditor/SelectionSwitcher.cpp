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

SelectionActionMode SelectionSwitcher::getActionMode() {
	return this->actionMode;
}

void SelectionSwitcher::setActionMode(SelectionActionMode _actionMode) {
	if (this->actionMode == _actionMode) return;

	this->actionMode = _actionMode;
}

void SelectionSwitcher::resetActionMode() {
	if (this->actionMode == SelectionActionMode::NONE) return;

	this->actionMode = SelectionActionMode::NONE;
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

void SelectionSwitcher::switchActionInput() {
	GLFWwindow* window = Application::getInstancePtr()->getWindow().getWindowPtr();

	if (!this->getSelection()->getSelectedObjects().empty()) {
		if (this->actionMode == SelectionActionMode::NONE) {
			double posX = 0.0;
			double posY = 0.0;
			glfwGetCursorPos(window, &posX, &posY);

			this->getSelection()->updateRelativeMousePosition(
				static_cast<float>(posX), static_cast<float>(posY)
			);
		}

		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
			this->setActionMode(SelectionActionMode::MOVING);
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			this->setActionMode(SelectionActionMode::ROTATION);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			this->setActionMode(SelectionActionMode::SCALING);

		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
			this->resetActionMode();
		}
	}

	switch (this->actionMode) {
		case SelectionActionMode::MOVING:
			this->getSelection()->moving();
			break;
		case SelectionActionMode::ROTATION:
			this->getSelection()->rotation();
			break;
		case SelectionActionMode::SCALING:
			this->getSelection()->scaling();
			break;
	}
}

void SelectionSwitcher::mouseActionInput(int button, int action, int mods) {
	if (this->actionMode == SelectionActionMode::NONE) return;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		this->resetActionMode();
	}
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
