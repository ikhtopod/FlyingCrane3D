#include "Scene.h"


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

void Scene::addObject(std::string _name, ObjectShape _object) {
	if (this->objects.empty() || (this->objects.find(_name) == this->objects.end())) {
		this->objects.insert({ _name, std::make_shared<ObjectShape>(_object) });
	}//fi
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

void Scene::init() {
	/***********************************/

	// grid
	this->addSceneObject("grid_8x8.000", ObjectSceneGrid { 8, 8 });

	// insert objects
	PolymeshRepresentation pyramid_polymesh_flat_000 {
		{
			Vertex{ { 1.0f, 0.0f, 1.0f },  { 0.0f, -1.0f, 0.0f }, 0 },
			Vertex{ { -1.0f, 0.0f, -1.0f }, { 0.0f, -1.0f, 0.0f }, 1 },
			Vertex{ { 1.0f, 0.0f, -1.0f }, { 0.0f, -1.0f, 0.0f }, 2 },

			Vertex{ { 1.0f, 0.0f, -1.0f }, { 0.8944f, 0.4472f, 0.0f }, 3 },
			Vertex{ { 0.0f, 2.0f, 0.0f }, { 0.8944f, 0.4472f, 0.0f }, 4 },
			Vertex{ { 1.0f, 0.0f, 1.0f },  { 0.8944f, 0.4472f, 0.0f }, 5 },

			Vertex{ { 1.0f, 0.0f, 1.0f },  { 0.0f, 0.4472f, 0.8944f }, 6 },
			Vertex{ { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.4472f, 0.8944f }, 7 },
			Vertex{ { -1.0f, 0.0f, 1.0f }, { 0.0f, 0.4472f, 0.8944f }, 8 },

			Vertex{ { -1.0f, 0.0f, 1.0f }, { -0.8944f, 0.4472f, 0.0f }, 9 },
			Vertex{ { 0.0f, 2.0f, 0.0f }, { -0.8944f, 0.4472f, 0.0f }, 10 },
			Vertex{ { -1.0f, 0.0f, -1.0f }, { -0.8944f, 0.4472f, 0.0f }, 11 },

			Vertex{ { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.4472f, -0.8944f }, 12 },
			Vertex{ { 1.0f, 0.0f, -1.0f }, { 0.0f, 0.4472f, -0.8944f }, 13 },
			Vertex{ { -1.0f, 0.0f, -1.0f }, { 0.0f, 0.4472f, -0.8944f }, 14 },

			Vertex{ { 1.0f, 0.0f, 1.0f },  { 0.0f, -1.0f, 0.0f }, 15 },
			Vertex{ { -1.0f, 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f }, 16 },
			Vertex{ { -1.0f, 0.0f, -1.0f }, { 0.0f, -1.0f, 0.0f }, 17 },
		},
		{
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
			9, 10, 11,
			12, 13, 14,
			15, 16, 17,
		}
	};

	Mesh pyramid_mesh_flat_000 { pyramid_polymesh_flat_000, GL_TRIANGLES };
	Mesh pyramid_mesh_flat_001 { pyramid_polymesh_flat_000, GL_TRIANGLES };

	ObjectShape pyramid_000 {};
	ObjectShape pyramid_001 {};

	pyramid_000.addMesh("pyramid_mesh_flat.000", pyramid_mesh_flat_000);
	pyramid_001.addMesh("pyramid_mesh_flat.000", pyramid_mesh_flat_001);

	pyramid_001.getTransform().setPosition(glm::vec3 { -3.0f, 0.0f, -1.0f });

	this->addObject("pyramid.000", pyramid_000);
	this->addObject("pyramid.001", pyramid_001);

	/***********************************/

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
