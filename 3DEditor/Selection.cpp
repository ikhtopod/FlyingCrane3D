#include "Selection.h"

Selection::Selection() :
	shader(R"(..\resources\shaders\Selection.vs)",
		   R"(..\resources\shaders\Selection.fs)") {}


bool Selection::diffIsZero() {
	return this->diffMousePosition.x == 0.0f && this->diffMousePosition.y == 0.0f;
}

std::map<std::string, Object*>& Selection::getSelectedObjects() {
	return this->selectedObjects;
}

bool Selection::hasSelectedObject(std::string name) {
	return this->selectedObjects.find(name) != this->selectedObjects.end();
}

bool Selection::hasSelectedObjects() {
	return !this->selectedObjects.empty();
}

void Selection::clearSelectedObjects() {
	for (auto&[objKey, objValue] : this->selectedObjects) {
		MeshElementManager& mem = objValue->getMeshElementManager();

		for (auto&[meshName, meshElements] : mem.getVertices()) {
			for (auto& mesh : meshElements) {
				mesh.getSelectionInfo().isSelected = false;
			}//rof
		}//rof mesh element vertices


		for (auto&[meshName, meshElements] : mem.getEdges()) {
			for (auto& mesh : meshElements) {
				mesh.getSelectionInfo().isSelected = false;
			}//rof
		}//rof mesh element edges

		for (auto&[meshName, meshElements] : mem.getFaces()) {
			for (auto& mesh : meshElements) {
				mesh.getSelectionInfo().isSelected = false;
			}//rof
		}//rof mesh element faces

		objValue->getSelectionInfo().isSelected = false;
	}//rof

	this->selectedObjects.clear();
}

void Selection::updateMousePosition() {
	Application* appThis = Application::getInstancePtr();
	double currentMouseX = 0.0;
	double currentMouseY = 0.0;

	glfwGetCursorPos(appThis->getWindow().getWindowPtr(), &currentMouseX, &currentMouseY);

	this->updateMousePosition(static_cast<float>(currentMouseX), static_cast<float>(currentMouseY));
}

void Selection::updateMousePosition(float currentMouseX, float currentMouseY) {
	if (this->prevMousePosition.x == currentMouseX &&
		this->prevMousePosition.y == currentMouseY) {

		this->diffMousePosition = glm::vec2 { };
	} else {
		float diffMouseX = prevMousePosition.y - static_cast<float>(currentMouseY);
		float diffMouseY = static_cast<float>(currentMouseX) - prevMousePosition.x;

		prevMousePosition = glm::vec2 { currentMouseX, currentMouseY };
		diffMousePosition = glm::vec2 { diffMouseY, diffMouseX };
	}
}

void Selection::mouseButtonInput(int button, int action, int mods) {
	if (button != GLFW_MOUSE_BUTTON_LEFT) return;

	static bool prevState = GLFW_RELEASE;

	if (action == GLFW_PRESS && prevState == GLFW_RELEASE) {
		if (mods != GLFW_MOD_SHIFT) {
			this->clearSelectedObjects();
		}//fi

		this->select();

		prevState = GLFW_PRESS;
	} else if (action == GLFW_RELEASE && prevState == GLFW_PRESS) {
		prevState = GLFW_RELEASE;
	}//esle fi
}


void Selection::init() {
	this->shader.init();
	this->shader.resetLambdaDraw();
}

void Selection::draw() { /* dummy */ }

void Selection::free() {
	this->shader.free();
	this->clearSelectedObjects();
}
