#include "Object.h"

Object::Object(std::string _name) : name(_name) {
	this->meshes.push_back(Mesh {});
}


std::string Object::getName() {
	return this->name;
}

void Object::setName(std::string _name) {
	this->name = _name;
}

void Object::init() {
	this->shader.init();

	for (Mesh& mesh : this->meshes) {
		mesh.init();
	}
}

void Object::draw() {
	this->shader.draw();

	for (Mesh& mesh : this->meshes) {
		mesh.draw();
	}
}

void Object::free() {
	this->shader.free();

	for (Mesh& mesh : this->meshes) {
		mesh.free();
	}
}
