#include "Object.h"


Transform& Object::getTransform() {
	return this->transform;
}

Transform& Object::getParentTransform() {
	return this->parentTransform;
}

Transform& Object::getGlobalTransform() {
	return this->globalTransform;
}

SelectionInfo& Object::getSelectionInfo() {
	return this->selectionInfo;
}


void Object::setTransform(Transform _transform) {
	this->transform = _transform;
	this->setGlobalTransform(this->getParentTransform() + this->getTransform());
}

void Object::setParentTransform(Transform _pTransform) {
	this->parentTransform = _pTransform;
	this->setGlobalTransform(this->getParentTransform() + this->getTransform());
}

void Object::setGlobalTransform(Transform _gTransform) {
	this->globalTransform = _gTransform;
}

void Object::setSelectionInfo(SelectionInfo _selectionInfo) {
	this->selectionInfo = _selectionInfo;
}


std::map<std::string, Mesh>& Object::getMeshes() {
	return this->meshes;
}

void Object::addMesh(std::string _name, Mesh& _mesh) {
	if (this->meshes.empty() || (this->meshes.find(_name) == this->meshes.end())) {
		this->meshes.insert({ _name, _mesh });
	}
}

void Object::setShadersAllMeshes(Shader& _shader) {
	for (auto& mesh : this->meshes) {
		mesh.second.setShader(_shader);
	}
}

void Object::resetShadersAllMeshes() {
	for (auto& mesh : this->meshes) {
		mesh.second.resetShaderToNative();
	}
}

std::map<std::string, Object>& Object::getChildrens() {
	return this->childrens;
}

void Object::addChildren(std::string _name, Object& _object) {
	if (this->childrens.empty() || (this->childrens.find(_name) == this->childrens.end())) {
		this->childrens.insert({ _name, _object });
	}
}

void Object::drawMeshes() {
	for (auto& mesh : this->meshes) {
		mesh.second.setParentTransform(this->parentTransform + this->transform);
		mesh.second.draw();
	}
}

void Object::drawChildrens() {
	for (auto& children : this->childrens) {
		children.second.setParentTransform(this->parentTransform + this->transform);
		children.second.draw();
	}
}


void Object::init() {
	for (auto& mesh : this->meshes) {
		mesh.second.init();
	}
}

void Object::draw() {
	this->drawMeshes();
	this->drawChildrens();
}

void Object::free() {
	for (auto& mesh : this->meshes) {
		mesh.second.free();
	}
}
