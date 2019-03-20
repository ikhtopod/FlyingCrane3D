#include "Object.h"


Transform& Object::getTransform() {
	return this->transform;
}

Transform& Object::getGlobalTransform() {
	return this->globalTransform;
}


void Object::setTransform(Transform _transform) {
	this->transform = _transform;
}

void Object::setGlobalTransform(Transform _gTransform) {
	this->globalTransform = _gTransform;
}


void Object::addMesh(std::string _name, Mesh& _mesh) {
	if (this->meshes.empty() || (this->meshes.find(_name) == this->meshes.end())) {
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
		mesh.second.setGlobalTransform(this->globalTransform + this->transform);
		mesh.second.draw();
	}
}

void Object::free() {
	for (auto& mesh : this->meshes) {
		mesh.second.free();
	}
}
