#pragma once

#include "Transform.h"
#include "Axis.h"
#include "Mesh.h"
#include "Shader.h"


class Object {
protected:
	std::string name;

	Transform transform {};
	Axis axis {};

	std::vector<Mesh> meshes;

	Shader shader {};

public:
	Object() = delete;
	Object(std::string _name);
	virtual ~Object() = default;

	std::string getName();
	void setName(std::string _name);

	void init();
	void draw();
	void free();

};
