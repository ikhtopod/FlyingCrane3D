#include "Selection.h"

Selection::Selection() :
	shader(R"(..\resources\shaders\Selection.vs)",
		   R"(..\resources\shaders\Selection.fs)") {}

std::map<std::string, Object*>& Selection::getSelectedObjects() {
	return this->selectedObjects;
}

bool Selection::hasSelectedObjects(std::string name) {
	return this->selectedObjects.find(name) != this->selectedObjects.end();
}

void Selection::clearSelectedObjects() {
	this->selectedObjects.clear();
}


void Selection::mouseButtonInput(int button, int action, int mods) {
	if (button != GLFW_MOUSE_BUTTON_LEFT) return;

	static bool prevState = GLFW_RELEASE;

	if (action == GLFW_PRESS && prevState == GLFW_RELEASE) {
		if (mods != GLFW_MOD_SHIFT)
			this->clearSelectedObjects();
		this->select();
		prevState = GLFW_PRESS;
	} else if (action == GLFW_RELEASE && prevState == GLFW_PRESS) {
		prevState = GLFW_RELEASE;
	}
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
