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

TriadaMode Object::getMode() {
	return this->mode;
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

MeshElementManager& Object::getMeshElementManager() {
	return this->mem;
}


Object::MapMesh& Object::getMeshes() {
	return this->meshes;
}

void Object::addMesh(std::string _name, Mesh& _mesh) {
	if (this->meshes.empty() || (this->meshes.find(_name) == this->meshes.end())) {
		this->meshes.insert({ _name, _mesh });
		this->mem.update();
	}//fi
}

void Object::setShadersAllMeshes(Shader& _shader) {
	for (auto&[meshName, mesh] : this->meshes) {
		mesh.setShader(_shader);
	}//rof
}

void Object::drawMeshes() {
	for (auto&[meshName, mesh] : this->meshes) {
		mesh.setParentTransform(this->parentTransform + this->transform);
		mesh.draw();
	}//rof
}


void Object::init() {
	this->mode = TriadaMode::INIT;

	for (auto&[meshName, mesh] : this->meshes) {
		mesh.init();
		mesh.getShader().setLambdaDraw([this](Shader* _this) {
			Application* appThis = Application::getInstancePtr();
			_this->setVec3("bgColor", glm::vec3 { appThis->getBgColor() });
			_this->setVec3("lightColor", glm::vec3 { 1.0f });
			_this->setVec3("objectColor", glm::vec3 { 0.78f, 0.78f, 0.78f });
			_this->setVec3("cameraPos", appThis->getScene().getCamera().getTransform().getPosition());
			_this->setBool("isSelectionProcess", this->getSelectionInfo().isSelectionProcess);
			_this->setBool("isSelected", this->getSelectionInfo().isSelected);
			_this->setVec4("colorCode", this->getSelectionInfo().colorSelect);
		});
	}//rof

	this->mem.init();
}

void Object::draw() {
	this->mode = TriadaMode::DRAW;

	if (this->selectionInfo.canSelect) {
		this->mem.setTransform(this->parentTransform + this->transform);
		this->mem.draw();
	}//fi

	this->drawMeshes();
}

void Object::free() {
	this->mode = TriadaMode::FREE;

	for (auto&[meshName, mesh] : this->meshes) {
		mesh.free();
	}//rof

	this->mem.free();

	this->mode = TriadaMode::NONE;
}
