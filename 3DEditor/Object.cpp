#include "Object.h"


Object* Object::getParent() {
	return this->parent;
}

Transform& Object::getTransform() {
	return this->transform;
}


void Object::setParent(Object* _parent) {
	this->parent = _parent;
}

void Object::setTransform(Transform _transform) {
	this->transform = _transform;
}

void Object::addMesh(std::string _name, Mesh _mesh) {
	if (this->meshes.empty() || (this->meshes.find(_name) == this->meshes.end())) {
		_mesh.setParent(this);
		this->meshes.insert({ _name, _mesh });
	}
}


void Object::init() {
	for (auto& mesh : this->meshes) {
		mesh.second.init();
	}
}

void Object::draw() {
	for (auto& mesh : this->meshes) {
		mesh.second.draw();
	}
}

void Object::free() {
	for (auto& mesh : this->meshes) {
		mesh.second.free();
	}
}
