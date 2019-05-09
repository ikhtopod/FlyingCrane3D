#pragma once

#include "ITriada.h"
#include "Transform.h"
#include "SelectionInfo.h"
#include "Mesh.h"
#include "MeshElementManager.h"
#include "Shader.h"


class Mesh;

class Object : public ITriada {
protected:
	template<class T>
	using UMap = std::unordered_map<std::string, T>;
	using UMapMesh = UMap<Mesh>;
	using UMapObject = UMap<Object>;

protected:
	Transform transform {};
	Transform parentTransform {};
	Transform globalTransform {};

	MeshElementManager mem { this };

	UMapMesh meshes {};

	SelectionInfo selectionInfo {};

public:
	Object() = default;
	virtual ~Object() = default;

	bool isDeleting = false;

	Transform& getTransform();
	Transform& getParentTransform();
	Transform& getGlobalTransform();
	SelectionInfo& getSelectionInfo();

	void setTransform(Transform _transform);
	void setParentTransform(Transform _pTransform);
	void setGlobalTransform(Transform _gTransform);
	void setSelectionInfo(SelectionInfo _selectionInfo);

	MeshElementManager& getMeshElementManager();

	UMapMesh& getMeshes();
	void addMesh(std::string _name, Mesh& _mesh);
	void setShadersAllMeshes(Shader& _shader);

	void drawMeshes();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
