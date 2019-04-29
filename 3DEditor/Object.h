#pragma once

#include "ITriada.h"
#include "Transform.h"
#include "SelectionInfo.h"
#include "Mesh.h"
#include "Shader.h"


class Mesh;

class Object : public ITriada {
protected:
	Transform transform {};
	Transform parentTransform {};
	Transform globalTransform {};

	std::map<std::string, Mesh> meshes {};
	std::map<std::string, Object> childrens {};

	SelectionInfo selectionInfo {};

public:
	Object() = default;
	virtual ~Object() = default;

	Transform& getTransform();
	Transform& getParentTransform();
	Transform& getGlobalTransform();
	SelectionInfo& getSelectionInfo();

	void setTransform(Transform _transform);
	void setParentTransform(Transform _pTransform);
	void setGlobalTransform(Transform _gTransform);
	void setSelectionInfo(SelectionInfo _selectionInfo);

	std::map<std::string, Mesh>& getMeshes();
	void addMesh(std::string _name, Mesh& _mesh);
	void setShadersAllMeshes(Shader& _shader);
	void resetShadersAllMeshes();

	std::map<std::string, Object>& getChildrens();
	void addChildren(std::string _name, Object& _object);

	void drawMeshes();
	void drawChildrens();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
