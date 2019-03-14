#include "Scene.h"


Camera& Scene::getCamera() {
	return this->camera;
}

Model& Scene::getModel() {
	return this->model;
}

Transform& Scene::getTransform() {
	return this->transform;
}

Axis& Scene::getAxis() {
	return this->axis;
}


void Scene::init() {
	// camera
	// grid
	//this->standardObjects.push_back(GridObject { "grid" });

	// insert objects
	std::string objName = "obj_01";

	auto exists_name_pred = [&objName](Object& o) -> bool {
		return objName == o.getName();
	};

	auto res = std::find_if(this->objects.begin(), this->objects.end(), exists_name_pred);

	if (res == this->objects.end()) {
		this->objects.push_back(Object { objName });
	}

	// sort by name
	auto sort_by_name_pred = [](Object o1, Object o2) -> bool {
		return o1.getName() < o2.getName();
	};

	std::sort(this->objects.begin(), this->objects.end(), sort_by_name_pred);


	// init objects
	for (Object& o : this->standardObjects) {
		o.init();
	}
	for (Object& o : this->objects) {
		o.init();
	}
}

void Scene::draw() {
	this->model.update();

	// draw objects
	for (Object& o : this->standardObjects) {
		o.draw();
	}
	for (Object& o : this->objects) {
		o.draw();
	}
}

void Scene::free() {
	// free objects
	for (Object& o : this->standardObjects) {
		o.free();
	}
	for (Object& o : this->objects) {
		o.free();
	}
}
