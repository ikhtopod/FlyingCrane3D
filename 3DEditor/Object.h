#pragma once

#include "Transform.h"
#include "Axis.h"
#include "Mesh.h"


class Object {
protected:
	std::string name;

	Transform transform {};
	Axis axis {};

	std::vector<Mesh> meshes;

public:
	Object() = delete;
	Object(std::string _name);
	virtual ~Object() = default;

	std::string getName();
	Transform& getTransform();

	void setName(std::string _name);
	void setTransform(Transform _transform);


	void init();
	void draw();
	void free();

};
