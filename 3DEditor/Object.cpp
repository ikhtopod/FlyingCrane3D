#include "Object.h"


Object::Object(std::string _name) : name(_name) {}


std::string Object::getName() {
	return this->name;
}

Transform& Object::getTransform() {
	return this->transform;
}

void Object::setName(std::string _name) {
	this->name = _name;
}

void Object::setTransform(Transform _transform) {
	this->transform = _transform;
}

void Object::addMesh(Mesh _mesh) {
	this->meshes.push_back(_mesh);
}


void Object::init() {
	for (Mesh& mesh : this->meshes) {
		mesh.init();
	}
}

void Object::draw() {
	for (Mesh& mesh : this->meshes) {
		mesh.draw();
	}
}

void Object::free() {
	for (Mesh& mesh : this->meshes) {
		mesh.free();
	}
}
