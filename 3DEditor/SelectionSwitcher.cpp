#include "SelectionSwitcher.h"


const SelectionMode SelectionSwitcher::DEFAULT_SELECTION_MODE = SelectionMode::OBJECT;


SelectionSwitcher::SelectionSwitcher() : selectionMode(DEFAULT_SELECTION_MODE) {
	selections.insert({ SelectionMode::VERTEX, std::make_shared<SelectionPoint>() });
	selections.insert({ SelectionMode::EDGE, std::make_shared<SelectionEdge>() });
	selections.insert({ SelectionMode::FACE, std::make_shared<SelectionFace>() });
	selections.insert({ SelectionMode::OBJECT, std::make_shared<SelectionObject>() });
}

SelectionMode SelectionSwitcher::getSelectionMode() {
	return this->selectionMode;
}

void SelectionSwitcher::setSelectionMode(SelectionMode _selectionMode) {
	if (this->selectionMode == _selectionMode || !this->hasSelection(_selectionMode)) return;

	this->getSelection()->clearSelectedObjects();
	this->selectionMode = _selectionMode;

}

bool SelectionSwitcher::hasSelection(SelectionMode _selectionMode) {
	return this->selections.find(_selectionMode) != this->selections.end();
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
	return this->selections[this->selectionMode];
}

void SelectionSwitcher::switchSelectionInput() {
	GLFWwindow* window = Application::getInstancePtr()->getWindow().getWindowPtr();

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		this->setSelectionMode(SelectionMode::VERTEX);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		this->setSelectionMode(SelectionMode::EDGE);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		this->setSelectionMode(SelectionMode::FACE);
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		this->setSelectionMode(SelectionMode::OBJECT);
}

void SelectionSwitcher::switchActionInput() {
	GLFWwindow* window = Application::getInstancePtr()->getWindow().getWindowPtr();

	if (!this->getSelection()->getSelectedObjects().empty()) {
		if (this->actionMode == SelectionActionMode::NONE) {
			double posX = 0.0;
			double posY = 0.0;
			glfwGetCursorPos(window, &posX, &posY);

			this->getSelection()->updateMousePosition(
				static_cast<float>(posX),
				static_cast<float>(posY)
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
	for (auto& selection : this->selections) {
		selection.second->free();
	}
}
