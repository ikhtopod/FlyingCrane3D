#include "Scene.h"


Scene::~Scene() {
	for (auto&[name, object] : this->sceneObjects) {
		if (object->getMode() == TriadaMode::INIT ||
			object->getMode() == TriadaMode::DRAW) {
			object->free();
		}
	}

	for (auto&[name, object] : this->objects) {
		if (object->getMode() == TriadaMode::INIT ||
			object->getMode() == TriadaMode::DRAW) {
			object->free();
		}
	}

	this->sceneObjects.clear();
	this->objects.clear();
}

CameraSwitcher& Scene::getCameraSwitcher() {
	return this->cameraSwitcher;
}

Camera& Scene::getCamera() {
	return *(this->cameraSwitcher.getCamera());
}

Model& Scene::getModel() {
	return this->model;
}

Transform& Scene::getTransform() {
	return this->transform;
}

SelectionSwitcher& Scene::getSelectionSwitcher() {
	return this->selectionSwitcher;
}

Selection& Scene::getSelection() {
	return *(this->selectionSwitcher.getSelection());
}

Scene::MapObjectShape& Scene::getObjects() {
	return this->objects;
}

void Scene::addSceneObject(std::string _name, ObjectScene _object) {
	if (this->sceneObjects.empty() || (this->sceneObjects.find(_name) == this->sceneObjects.end())) {
		this->sceneObjects.insert({ _name, std::make_shared<ObjectScene>(_object) });
	}//fi
}


void Scene::addObject(ObjectShape& _object) {
	this->addObject("object", _object);
}

void Scene::addObject(const std::string& _name, ObjectShape& _object) {
	std::string objectName = _name;

	std::size_t counter = 0;
	while (this->objects.find(objectName) != this->objects.cend()) {
		std::string postfix = std::to_string(counter++);

		objectName = _name + '.';

		if (postfix.size() < 3) {
			objectName += std::string(3 - postfix.size(), '0');
		}

		objectName += postfix;
	}//fi

	this->objects.insert({ objectName, std::make_shared<ObjectShape>(_object) });
}


void Scene::deleteMarkedObjects() {
	std::vector<std::string> namesForDelete {};

	for (auto&[name, object] : this->objects) {
		if (object->isDeleting) {
			object->free();
			namesForDelete.push_back(name);
		}//fi
	}//rof


	if (namesForDelete.empty()) return;

	for (std::string& name : namesForDelete) {
		this->objects.erase(name);
	}//rof
}

void Scene::initSceneObjects() {
	this->addSceneObject("grid_8x8.000", ObjectSceneGrid { 8, 8 });
}

void Scene::init() {
	this->initSceneObjects();

	for (auto&[name, object] : this->sceneObjects) {
		object->init();
	}//rof

	for (auto&[name, object] : this->objects) {
		object->init();
	}//rof
}

void Scene::draw() {
	this->model.update();

	for (auto&[name, object] : this->sceneObjects) {
		object->setParentTransform(this->transform);
		object->draw();
	}//rof

	this->deleteMarkedObjects();

	for (auto&[name, object] : this->objects) {
		object->setParentTransform(this->transform);
		object->draw();
	}//rof
}

void Scene::free() {
	for (auto&[name, object] : this->sceneObjects) {
		object->free();
	}//rof

	for (auto&[name, object] : this->objects) {
		object->free();
	}//rof

	this->selectionSwitcher.clearSelections();
}
