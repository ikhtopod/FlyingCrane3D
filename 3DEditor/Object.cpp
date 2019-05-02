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


void Object::updateMeshVertices() {
	for (auto&[key, value] : this->meshVertices) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof

		value.clear();
	}//rof

	this->meshVertices.clear();

	for (auto&[meshName, mesh] : this->meshes) {
		this->meshVertices.insert({ meshName, std::vector<MeshElementVertex> {} });

		for (Vertex& vertex : mesh.getPolymesh().getVertices()) {
			MeshElementVertex mev { vertex };
			this->meshVertices[meshName].push_back(mev);
			this->meshVertices[meshName].back().init();
		}//rof
	}//rof
}

Object::UMapMesh& Object::getMeshes() {
	return this->meshes;
}

void Object::addMesh(std::string _name, Mesh& _mesh) {
	if (this->meshes.empty() || (this->meshes.find(_name) == this->meshes.end())) {
		this->meshes.insert({ _name, _mesh });
		this->updateMeshVertices();
	}//fi
}

void Object::setShadersAllMeshes(Shader& _shader) {
	for (auto&[meshName, mesh] : this->meshes) {
		mesh.setShader(_shader);
	}//rof
}

void Object::resetShadersAllMeshes() {
	for (auto&[meshName, mesh] : this->meshes) {
		mesh.resetShaderToNative();
	}//rof
}

Object::UMapObject& Object::getChildrens() {
	return this->childrens;
}

void Object::addChildren(std::string _name, Object& _object) {
	if (this->childrens.empty() || (this->childrens.find(_name) == this->childrens.end())) {
		this->childrens.insert({ _name, _object });
	}//fi
}

void Object::drawMeshes() {
	for (auto&[meshName, mesh] : this->meshes) {
		mesh.setParentTransform(this->parentTransform + this->transform);
		mesh.draw();
	}//rof
}

void Object::drawMeshVertices() {
	for (auto&[key, value] : this->meshVertices) {
		for (auto& mesh : value) {
			mesh.setParentTransform(this->parentTransform + this->transform);
			mesh.draw();
		}//rof
	}//rof
}

void Object::drawElements() {
	if (!this->selectionInfo.canSelect) return;

	SelectionMode sm = Application::getInstancePtr()->
		getScene().getSelectionSwitcher().getSelectionMode();

	switch (sm) {
		case SelectionMode::VERTEX:
			this->drawMeshVertices();
			break;
		case SelectionMode::EDGE:
			break;
		case SelectionMode::FACE:
			break;
	}
}

void Object::drawChildrens() {
	for (auto& children : this->childrens) {
		children.second.setParentTransform(this->parentTransform + this->transform);
		children.second.draw();
	}//rof
}


void Object::init() {
	for (auto&[meshName, mesh] : this->meshes) {
		mesh.init();
	}//rof

	for (auto&[key, value] : this->meshVertices) {
		for (auto& mesh : value) {
			mesh.init();
		}//rof
	}//rof
}

void Object::draw() {
	this->drawElements();
	this->drawMeshes();
	this->drawChildrens();
}

void Object::free() {
	for (auto&[meshName, mesh] : this->meshes) {
		mesh.free();
	}//rof

	for (auto&[key, value] : this->meshVertices) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof
	}//rof
}
