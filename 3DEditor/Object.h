#pragma once

#include "Transform.h"
#include "Axis.h"
#include "Mesh.h"


class Object {
protected:
	Transform transform {};
	Axis axis {};

	std::map<std::string, Mesh> meshes;

public:
	Object() = default;
	virtual ~Object() = default;

	Transform& getTransform();

	void setTransform(Transform _transform);

	void addMesh(std::string _name, Mesh _mesh);

	void init();
	void draw();
	void free();

};
