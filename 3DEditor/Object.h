#pragma once

#include "ITriada.h"
#include "Transform.h"
#include "Axis.h"
#include "Mesh.h"


class Mesh;

class Object : public ITriada {
protected:
	Object* parent = nullptr;

	Transform transform {};
	Axis axis {};

	std::map<std::string, Mesh> meshes;

public:
	Object() = default;
	virtual ~Object() = default;

	Object* getParent();
	Transform& getTransform();

	void setParent(Object* _parent);
	void setTransform(Transform _transform);

	void addMesh(std::string _name, Mesh& _mesh);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
