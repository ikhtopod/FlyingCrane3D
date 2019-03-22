#pragma once

#include "Camera.h"
#include "TargetCamera.h"
#include "FreeCamera.h"


enum class CameraType : unsigned short {
	TARGET, FREE
};


class CameraSwitcher {
public:
	static const CameraType DEFAULT_CAMERA_TYPE;

private:
	CameraType type;
	std::unordered_map<CameraType, std::shared_ptr<Camera>> cameras {};

private:
	void updateInputMode();

public:
	CameraSwitcher();
	~CameraSwitcher() = default;

	CameraType getType();
	void setType(CameraType _type);

	std::shared_ptr<Camera> getCamera();
	void switchCamera();
};
