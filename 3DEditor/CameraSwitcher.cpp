#include "CameraSwitcher.h"


const CameraType CameraSwitcher::DEFAULT_CAMERA_TYPE = CameraType::TARGET;


CameraSwitcher::CameraSwitcher() : type(CameraSwitcher::DEFAULT_CAMERA_TYPE) {
	cameras.insert({ CameraType::TARGET, std::make_shared<TargetCamera>() });
	cameras.insert({ CameraType::FREE, std::make_shared<FreeCamera>() });
}

CameraType CameraSwitcher::getType() const {
	return this->type;
}

void CameraSwitcher::setType(CameraType _type) {
	if (this->type == _type || !this->hasCamera(_type)) return;

	this->cameras[_type]->setTransform(this->getCamera()->getTransform());
	this->cameras[_type]->setAxis(this->getCamera()->getAxis());
	this->cameras[_type]->setLastMousePosition(this->getCamera()->getLastMousePosition());
	this->cameras[_type]->spin();
	this->type = _type;

	this->updateInputMode();
}

void CameraSwitcher::updateInputMode() const {
	GLFWwindow* window = Application::getInstancePtr()->getWindow().getWindowPtr();

	switch (this->type) {
		case CameraType::TARGET:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case CameraType::FREE:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		default:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
	}
}

bool CameraSwitcher::hasCamera(CameraType _type) {
	return this->cameras.find(_type) != this->cameras.end();
}

std::shared_ptr<Camera> CameraSwitcher::getCamera() {
	return this->cameras[this->type];
}

void CameraSwitcher::switchCamera() {
	Application* appThis = Application::getInstancePtr();

	switch (this->type) {
		case CameraType::TARGET:
			if (appThis->getScene().getModel().getOrthoProj().isPerspective()) {
				this->setType(CameraType::FREE);
			}
			break;
		case CameraType::FREE:
			this->setType(CameraType::TARGET);
			break;
		default:
			this->setType(CameraSwitcher::DEFAULT_CAMERA_TYPE);
			break;
	}
}

