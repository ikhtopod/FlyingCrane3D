#pragma once

#include "ITriada.h"
#include "Transform.h"
#include "SelectionInfo.h"
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "MeshElementVertex.h"
#include "Shader.h"


class Mesh;
class MeshElementVertex;

class Object : public ITriada {
protected:
	// явл€етс€ ли класс D подклассом класса B
	template<class B, class D>
	using IsBaseOf = std::enable_if_t<std::is_base_of_v<B, D>>;

	// явл€етс€ ли класс D подклассом класса MeshElement
	template<class D>
	using IsBaseOfMeshElement = IsBaseOf<MeshElement, D>;

	// ќтображение списка объектов, €вл€ющихс€ подклассами класса MeshElement
	template<typename T, typename = IsBaseOfMeshElement<T>>
	using MapMeshElements = std::unordered_map<std::string, std::vector<T>>;

	template<class T>
	using UnorderedMap = std::unordered_map<std::string, T>;
	using UnorderedMapMesh = UnorderedMap<Mesh>;
	using UnorderedMapObject = UnorderedMap<Object>;

protected:
	Transform transform {};
	Transform parentTransform {};
	Transform globalTransform {};

	MapMeshElements<MeshElementVertex> meshVertices {};
	UnorderedMapMesh meshes {};
	UnorderedMapObject childrens {};

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

	UnorderedMapMesh& getMeshes();
	void addMesh(std::string _name, Mesh& _mesh);
	void setShadersAllMeshes(Shader& _shader);
	void resetShadersAllMeshes();

	void updateMeshVertices();

	UnorderedMapObject& getChildrens();
	void addChildren(std::string _name, Object& _object);

	void drawMeshVertices();

	void drawElements();
	void drawMeshes();
	void drawChildrens();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
