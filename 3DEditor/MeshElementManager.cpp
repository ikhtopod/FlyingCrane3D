#include "MeshElementManager.h"


void MeshElementManager::updateSelectionMode() {
	this->currentSelectionMode = Application::getInstancePtr()->
		getScene().getSelectionSwitcher().getSelectionMode();
}

void MeshElementManager::updateMeshVertices() {
	for (auto&[key, value] : this->vertices) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof

		value.clear();
	}//rof

	this->vertices.clear();

	if (this->meshes == nullptr) return;

	for (auto&[meshName, mesh] : *this->meshes) {
		this->vertices.insert({ meshName, std::vector<MeshElementVertex> {} });

		for (Vertex& vertex : mesh.getPolymesh().getVertices()) {
			MeshElementVertex me { vertex };
			this->vertices[meshName].push_back(me);
			this->vertices[meshName].back().init();
		}//rof
	}//rof
}

void MeshElementManager::updateMeshEdges() {
	for (auto&[key, value] : this->edges) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof

		value.clear();
	}//rof

	this->edges.clear();

	if (this->meshes == nullptr) return;

	for (auto&[meshName, mesh] : *this->meshes) {
		this->edges.insert({ meshName, std::vector<MeshElementEdge> {} });

		for (Edge& edge : mesh.getPolymesh().getEdges()) {
			MeshElementEdge me { edge };
			this->edges[meshName].push_back(me);
			this->edges[meshName].back().init();
		}//rof
	}//rof
}

void MeshElementManager::updateMeshFaces() {
	for (auto&[key, value] : this->faces) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof

		value.clear();
	}//rof

	this->faces.clear();

	if (this->meshes == nullptr) return;

	for (auto&[meshName, mesh] : *this->meshes) {
		this->faces.insert({ meshName, std::vector<MeshElementFace> {} });

		for (Face& face : mesh.getPolymesh().getFaces()) {
			MeshElementFace me { face };
			this->faces[meshName].push_back(me);
			this->faces[meshName].back().init();
		}//rof
	}//rof
}

void MeshElementManager::drawMeshVertices() {
	for (auto&[key, value] : this->vertices) {
		for (MeshElementVertex& mesh : value) {
			mesh.setParentTransform(this->transform);
			mesh.draw();
		}//rof
	}//rof
}

void MeshElementManager::drawMeshEdges() {
	for (auto&[key, value] : this->edges) {
		for (MeshElementEdge& mesh : value) {
			mesh.setParentTransform(this->transform);
			mesh.draw();
		}//rof
	}//rof
}

void MeshElementManager::drawMeshFaces() {
	for (auto&[key, value] : this->faces) {
		for (MeshElementFace& mesh : value) {
			mesh.setParentTransform(this->transform);
			mesh.draw();
		}//rof
	}//rof
}



void MeshElementManager::updateMeshElements(UMapMesh* _meshes) {
	this->meshes = _meshes;

	this->updateMeshVertices();
	this->updateMeshEdges();
	this->updateMeshFaces();
}


Transform& MeshElementManager::getTransform() {
	return this->transform;
}

void MeshElementManager::setTransform(Transform _transform) {
	this->transform = _transform;
}


void MeshElementManager::init() {
	for (auto&[key, value] : this->vertices) {
		for (auto& mesh : value) {
			mesh.init();
		}//rof
	}//rof

	for (auto&[key, value] : this->edges) {
		for (auto& mesh : value) {
			mesh.init();
		}//rof
	}//rof

	for (auto&[key, value] : this->faces) {
		for (auto& mesh : value) {
			mesh.init();
		}//rof
	}//rof
}

void MeshElementManager::draw() {
	this->updateSelectionMode();

	switch (this->currentSelectionMode) {
		case SelectionMode::VERTEX:
			this->drawMeshVertices();
			break;
		case SelectionMode::EDGE:
			glLineWidth(2.0f);
			this->drawMeshEdges();
			glLineWidth(1.0f);
			break;
		case SelectionMode::FACE:
			this->drawMeshFaces();
			break;
	}
}

void MeshElementManager::free() {
	for (auto&[key, value] : this->vertices) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof
	}//rof

	for (auto&[key, value] : this->edges) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof
	}//rof

	for (auto&[key, value] : this->faces) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof
	}//rof
}


