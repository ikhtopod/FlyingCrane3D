#include "MeshElementManager.h"


void MeshElementManager::updateSelectionMode() {
	this->currentSelectionMode = Application::getInstancePtr()->
		getScene().getSelectionSwitcher().getSelectionMode();
}


template<typename T>
void MeshElementManager::cleaner(T* data) {
	for (auto&[key, value] : *data) {
		for (auto& mesh : value) {
			mesh->free();
		}//rof

		value.clear();
	}//rof

	data->clear();
}

template<typename T>
void MeshElementManager::initializer(T* data) {
	for (auto&[key, value] : *data) {
		for (auto& mesh : value) {
			mesh->init();
		}//rof
	}//rof
}

template<typename T>
void MeshElementManager::_paint(T* data, Transform _transform, bool _painting) {
	for (auto&[key, value] : *data) {
		for (auto& mesh : value) {
			if (!mesh->getSelectionInfo().canSelect) continue;
			if (mesh->getSelectionInfo().isSelected != _painting) continue;

			mesh->setParentTransform(_transform);
			mesh->draw();
		}//rof
	}//rof
}

template<typename T>
void MeshElementManager::_paintNotSelected(T* data, Transform _transform) {
	_paint<T>(data, _transform, false);
}

template<typename T>
void MeshElementManager::_paintSelected(T* data, Transform _transform) {
	_paint<T>(data, _transform, true);
}

template<typename T>
void MeshElementManager::painter(T* data, Transform _transform) {
	// Сперва отрисовывать выделенные элементы, затем - не выделенные.
	// Это нужно для корректной отрисовки выделения.
	_paintSelected<T>(data, _transform);
	_paintNotSelected<T>(data, _transform);
}

template<typename T>
void MeshElementManager::liberator(T* data) {
	for (auto&[key, value] : *data) {
		for (auto& mesh : value) {
			mesh->free();
		}//rof
	}//rof
}


void MeshElementManager::updatePoints() {
	cleaner<decltype(this->points)>(&this->points);

	for (auto&[meshName, mesh] : *this->meshes) {
		this->points.insert({ meshName, VectorPtr<MeshElementPoint> {} });

		for (Point& point : mesh.getPolymesh().getPoints()) {
			this->points[meshName].push_back(std::make_shared<MeshElementPoint>(&point));
			this->points[meshName].back()->init();
		}//rof
	}//rof
}

void MeshElementManager::updateEdges() {
	cleaner<decltype(this->edges)>(&this->edges);

	for (auto&[meshName, mesh] : *this->meshes) {
		this->edges.insert({ meshName, VectorPtr<MeshElementEdge> {} });

		for (Edge& edge : mesh.getPolymesh().getEdges()) {
			this->edges[meshName].push_back(std::make_shared<MeshElementEdge>(&edge));
			this->edges[meshName].back()->init();
		}//rof
	}//rof
}

void MeshElementManager::updateFaces() {
	cleaner<decltype(this->faces)>(&this->faces);

	for (auto&[meshName, mesh] : *this->meshes) {
		this->faces.insert({ meshName, VectorPtr<MeshElementFace> {} });

		for (Face& face : mesh.getPolymesh().getFaces()) {
			this->faces[meshName].push_back(std::make_shared<MeshElementFace>(&face));
			this->faces[meshName].back()->init();
		}//rof
	}//rof
}


void MeshElementManager::update(UMapMesh* _meshes) {
	if (_meshes == nullptr) return;

	this->meshes = _meshes;

	this->updatePoints();
	this->updateEdges();
	this->updateFaces();
}


Transform& MeshElementManager::getTransform() {
	return this->transform;
}

void MeshElementManager::setTransform(Transform _transform) {
	this->transform = _transform;
}

MeshElementManager::UMapMeshElements<MeshElementPoint>&
MeshElementManager::getPoints() {
	return this->points;
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
	initializer<decltype(this->points)>(&this->points);
	initializer<decltype(this->edges)>(&this->edges);
	initializer<decltype(this->faces)>(&this->faces);
}

void MeshElementManager::draw() {
	this->updateSelectionMode();

	switch (this->currentSelectionMode) {
		case SelectionMode::POINT:
			painter<decltype(this->points)>(&this->points, this->transform);
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
	liberator<decltype(this->points)>(&this->points);
	liberator<decltype(this->edges)>(&this->edges);
	liberator<decltype(this->faces)>(&this->faces);
}


