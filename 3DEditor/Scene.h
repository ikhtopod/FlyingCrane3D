#pragma once

#include "Object.h"
#include "GridObject.h"
#include "Camera.h"
#include "Model.h"
#include "Transform.h"
#include "Axis.h"

class Scene final {
private:
	Camera camera {};
	Model model {};
	Transform transform {};
	Axis axis {};

public:
	std::vector<Object> standardObjects {};
	std::vector<Object> objects {};

public:
	Scene() = default;
	~Scene() = default;

	Camera& getCamera();
	Model& getModel();
	Transform& getTransform();
	Axis& getAxis();

	void init();
	void draw();
	void free();
};
