#include "MeshElementManager.h"


void MeshElementManager::updateSelectionMode() {
	this->currentSelectionMode = Application::getInstancePtr()->
		getScene().getSelectionSwitcher().getSelectionMode();
}


template<typename T>
void MeshElementManager::cleaner(T* data) {
	for (auto&[key, value] : *data) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof

		value.clear();
	}//rof

	data->clear();
}

template<typename T>
void MeshElementManager::initializer(T* data) {
	for (auto&[key, value] : *data) {
		for (auto& mesh : value) {
			mesh.init();
		}//rof
	}//rof
}

template<typename T>
void MeshElementManager::painter(T* data, Transform _transform) {
	for (auto&[key, value] : *data) {
		for (auto& mesh : value) {
			mesh.setParentTransform(_transform);
			mesh.draw();
		}//rof
	}//rof
}

template<typename T>
void MeshElementManager::liberator(T* data) {
	for (auto&[key, value] : *data) {
		for (auto& mesh : value) {
			mesh.free();
		}//rof
	}//rof
}


void MeshElementManager::updateVertices() {
	cleaner<decltype(this->vertices)>(&this->vertices);

	for (auto&[meshName, mesh] : *this->meshes) {
		this->vertices.insert({ meshName, std::vector<MeshElementVertex> {} });

		for (Vertex& vertex : mesh.getPolymesh().getVertices()) {
			this->vertices[meshName].push_back({ vertex });
			this->vertices[meshName].back().init();
		}//rof
	}//rof
}

void MeshElementManager::updateEdges() {
	cleaner<decltype(this->edges)>(&this->edges);

	for (auto&[meshName, mesh] : *this->meshes) {
		this->edges.insert({ meshName, std::vector<MeshElementEdge> {} });

		for (Edge& edge : mesh.getPolymesh().getEdges()) {
			this->edges[meshName].push_back({ edge });
			this->edges[meshName].back().init();
		}//rof
	}//rof
}

void MeshElementManager::updateFaces() {
	cleaner<decltype(this->faces)>(&this->faces);

	for (auto&[meshName, mesh] : *this->meshes) {
		this->faces.insert({ meshName, std::vector<MeshElementFace> {} });

		for (Face& face : mesh.getPolymesh().getFaces()) {
			this->faces[meshName].push_back({ face });
			this->faces[meshName].back().init();
		}//rof
	}//rof
}


void MeshElementManager::update(UMapMesh* _meshes) {
	if (_meshes == nullptr) return;

	this->meshes = _meshes;

	this->updateVertices();
	this->updateEdges();
	this->updateFaces();
}


Transform& MeshElementManager::getTransform() {
	return this->transform;
}

void MeshElementManager::setTransform(Transform _transform) {
	this->transform = _transform;
}

MeshElementManager::UMapMeshElements<MeshElementVertex>&
MeshElementManager::getVertices() {
	return this->vertices;
}

MeshElementManager::UMapMeshElements<MeshElementEdge>&
MeshElementManager::getEdges() {
	return this->edges;
}

MeshElementManager::UMapMeshElements<MeshElementFace>&
MeshElementManager::getFaces() {
	return this->faces;
}


void MeshElementManager::init() {
	initializer<decltype(this->vertices)>(&this->vertices);
	initializer<decltype(this->edges)>(&this->edges);
	initializer<decltype(this->faces)>(&this->faces);
}

void MeshElementManager::draw() {
	this->updateSelectionMode();

	switch (this->currentSelectionMode) {
		case SelectionMode::VERTEX:
			painter<decltype(this->vertices)>(&this->vertices, this->transform);
			break;
		case SelectionMode::EDGE:
			glLineWidth(2.5f);
			painter<decltype(this->edges)>(&this->edges, this->transform);
			glLineWidth(1.0f);
			break;
		case SelectionMode::FACE:
			painter<decltype(this->faces)>(&this->faces, this->transform);
			break;
	}
}

void MeshElementManager::free() {
	liberator<decltype(this->vertices)>(&this->vertices);
	liberator<decltype(this->edges)>(&this->edges);
	liberator<decltype(this->faces)>(&this->faces);
}


