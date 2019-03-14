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

void Scene::addStandardObject(std::string _name, Object _object) {
	if (this->standardObjects.empty() || (this->standardObjects.find(_name) == this->standardObjects.end())) {
		this->standardObjects.insert({ _name, _object });
	}
}

void Scene::addObject(std::string _name, Object _object) {
	if (this->objects.empty() || (this->objects.find(_name) == this->objects.end())) {
		this->objects.insert({ _name, _object });
	}
}


void Scene::init() {
	// grid
	this->addStandardObject("grid.001", GridObject {});

	// insert objects
	Object obj1 {};
	obj1.addMesh("mesh.001", Mesh {});
	this->addObject("object.001", obj1);

	// init objects
	for (auto& o : this->standardObjects) {
		o.second.init();
	}

	for (auto& o : this->objects) {
		o.second.init();
	}
}

void Scene::draw() {
	this->model.update();

	// draw objects
	for (auto& o : this->standardObjects) {
		o.second.draw();
	}

	for (auto& o : this->objects) {
		o.second.draw();
	}
}

void Scene::free() {
	// free objects
	for (auto& o : this->standardObjects) {
		o.second.free();
	}

	for (auto& o : this->objects) {
		o.second.free();
	}
}
