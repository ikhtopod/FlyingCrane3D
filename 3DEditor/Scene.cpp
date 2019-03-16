#include "Scene.h"


Camera& Scene::getCamera() {
	return this->camera;
}

Model& Scene::getModel() {
	return this->model;
}

Transform& Scene::getTransform() {
	return this->transform;
}

Axis& Scene::getAxis() {
	return this->axis;
}

void Scene::addStandardObject(std::string _name, Object _object) {
	if (this->standardObjects.empty() || (this->standardObjects.find(_name) == this->standardObjects.end())) {
		this->standardObjects.insert({ _name, _object });
	}
}

void Scene::addObject(std::string _name, Object _object) {
	if (this->objects.empty() || (this->objects.find(_name) == this->objects.end())) {
		this->objects.insert({ _name, _object });
	}
}


void Scene::init() {
	// grid
	this->addStandardObject("grid_8x8.000", GridObject { 8, 8 });

	// insert objects
	Object pyramid_000 {};
	Mesh pyramid_mesh_flat_000 {
		{
			Vertex{ { 1.0f, 0.0f, 1.0f },  { 0.0f, -1.0f, 0.0f } },
			Vertex{ { -1.0f, 0.0f, -1.0f }, { 0.0f, -1.0f, 0.0f } },
			Vertex{ { 1.0f, 0.0f, -1.0f }, { 0.0f, -1.0f, 0.0f } },

			Vertex{ { 1.0f, 0.0f, -1.0f }, { 0.8944f, 0.4472f, 0.0f } },
			Vertex{ { 0.0f, 2.0f, 0.0f }, { 0.8944f, 0.4472f, 0.0f } },
			Vertex{ { 1.0f, 0.0f, 1.0f },  { 0.8944f, 0.4472f, 0.0f } },

			Vertex{ { 1.0f, 0.0f, 1.0f },  { 0.0f, 0.4472f, 0.8944f } },
			Vertex{ { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.4472f, 0.8944f } },
			Vertex{ { -1.0f, 0.0f, 1.0f }, { 0.0f, 0.4472f, 0.8944f } },

			Vertex{ { -1.0f, 0.0f, 1.0f }, { -0.8944f, 0.4472f, 0.0f } },
			Vertex{ { 0.0f, 2.0f, 0.0f }, { -0.8944f, 0.4472f, 0.0f } },
			Vertex{ { -1.0f, 0.0f, -1.0f }, { -0.8944f, 0.4472f, 0.0f } },

			Vertex{ { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.4472f, -0.8944f } },
			Vertex{ { 1.0f, 0.0f, -1.0f }, { 0.0f, 0.4472f, -0.8944f } },
			Vertex{ { -1.0f, 0.0f, -1.0f }, { 0.0f, 0.4472f, -0.8944f } },

			Vertex{ { 1.0f, 0.0f, 1.0f },  { 0.0f, -1.0f, 0.0f } },
			Vertex{ { -1.0f, 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },
			Vertex{ { -1.0f, 0.0f, -1.0f }, { 0.0f, -1.0f, 0.0f } },
		},
		{
			0, 1, 2,
			3, 4, 5,
			6, 7, 8,
			9, 10, 11,
			12, 13, 14,
			15, 16, 17,
		},
		GL_TRIANGLES
	};

	/*Mesh pyramid_mesh_smooth_000 {
		{
			Vertex{ { 1.0f, 0.0f, -1.0f }, { 0.0f, -1.0f, 0.0f } },
			Vertex{ { 1.0f, 0.0f, 1.0f },  { 0.8944f, 0.4472f, 0.0f } },
			Vertex{ { -1.0f, 0.0f, 1.0f }, { 0.0f, 0.4472f, 0.8944f } },
			Vertex{ { -1.0f, 0.0f, -1.0f }, { -0.8944f, 0.4472f, 0.0f } },
			Vertex{ { 0.0f, 2.0f, 0.0f }, { 0.0f, 0.4472f, -0.8944f } },
		},
		{
			1, 3, 0,
			0, 4, 1,
			1, 4, 2,
			2, 4, 3,
			4, 0, 3,
			1, 2, 3,
		},
		GL_TRIANGLES
	};*/

	pyramid_000.addMesh("pyramid_mesh_flat.000", pyramid_mesh_flat_000);
	this->addObject("pyramid.000", pyramid_000);

	// init objects
	for (auto& o : this->standardObjects) {
		o.second.init();
	}

	for (auto& o : this->objects) {
		o.second.init();
	}
}

void Scene::draw() {
	this->model.update();

	// draw objects
	for (auto& o : this->standardObjects) {
		o.second.draw();
	}

	for (auto& o : this->objects) {
		o.second.draw();
	}
}

void Scene::free() {
	// free objects
	for (auto& o : this->standardObjects) {
		o.second.free();
	}

	for (auto& o : this->objects) {
		o.second.free();
	}
}
