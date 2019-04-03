#pragma once

#include "ITriada.h"
#include "Transform.h"
#include "Mesh.h"


class Mesh;

class Object : public ITriada {
protected:
	Transform transform {};
	Transform globalTransform {};

	std::map<std::string, Mesh> meshes;

public:
	bool canSelect = true;
	glm::vec4 colorSelect = glm::vec4 {};

public:
	Object() = default;
	virtual ~Object() = default;

	Transform& getTransform();
	Transform& getGlobalTransform();

	void setTransform(Transform _transform);
	void setGlobalTransform(Transform _gTransform);

	std::map<std::string, Mesh>& getMeshes();
	void addMesh(std::string _name, Mesh& _mesh);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
