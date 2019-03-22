#include "CameraSwitcher.h"


const CameraType CameraSwitcher::DEFAULT_CAMERA_TYPE = CameraType::TARGET;


CameraSwitcher::CameraSwitcher() : type(CameraSwitcher::DEFAULT_CAMERA_TYPE) {
	cameras.insert({ CameraType::TARGET, std::make_shared<TargetCamera>() });
	cameras.insert({ CameraType::FREE, std::make_shared<FreeCamera>() });
}

CameraType CameraSwitcher::getType() {
	return this->type;
}

void CameraSwitcher::setType(CameraType _type) {
	this->type = _type;
}

std::shared_ptr<Camera> CameraSwitcher::getCamera() {
	return this->cameras[this->type];
}

void CameraSwitcher::switchCamera() {
	switch (this->type) {
		case CameraType::TARGET:
			this->setType(CameraType::FREE);
			break;
		case CameraType::FREE:
			this->setType(CameraType::TARGET);
			break;
		default:
			this->setType(CameraSwitcher::DEFAULT_CAMERA_TYPE);
			break;
	}
}

