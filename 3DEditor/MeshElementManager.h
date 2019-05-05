#pragma once

#include "ITriada.h"
#include "Transform.h"
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "MeshElementVertex.h"
#include "MeshElementEdge.h"
#include "MeshElementFace.h"
#include "SelectionSwitcher.h"


class MeshElementManager final : public ITriada {
private:
	// явл€етс€ ли класс D подклассом класса B
	template<class B, class D>
	using IsBaseOf = std::enable_if_t<std::is_base_of_v<B, D>>;

	// явл€етс€ ли класс D подклассом класса MeshElement
	template<class D>
	using IsBaseOfMeshElement = IsBaseOf<MeshElement, D>;

	template<typename T>
	using VectorPtr = std::vector<std::shared_ptr<T>>;

	// ќтображение списка объектов, €вл€ющихс€ подклассами класса MeshElement
	template<typename T, typename = IsBaseOfMeshElement<T>>
	using UMapMeshElements = std::unordered_map<std::string, VectorPtr<T>>;

	template<class T>
	using UMap = std::unordered_map<std::string, T>;
	using UMapMesh = UMap<Mesh>;

private:
	UMapMeshElements<MeshElementVertex> vertices {};
	UMapMeshElements<MeshElementEdge> edges {};
	UMapMeshElements<MeshElementFace> faces {};

	SelectionMode currentSelectionMode = SelectionMode::OBJECT;

	Transform transform {};
	UMapMesh* meshes = nullptr;

public:
	MeshElementManager() = default;
	~MeshElementManager() = default;

private:
	template<typename T>
	static void cleaner(T* data);

	template<typename T>
	static void initializer(T* data);

	template<typename T>
	static void _paint(T* data, Transform _transform, bool _painting);
	template<typename T>
	static void _paintNotSelected(T* data, Transform _transform);
	template<typename T>
	static void _paintSelected(T* data, Transform _transform);
	template<typename T>
	static void painter(T* data, Transform _transform);

	template<typename T>
	static void liberator(T* data);

private:
	void updateSelectionMode();

	void updateVertices();
	void updateEdges();
	void updateFaces();

public:
	void update(UMapMesh* _meshes);

	Transform& getTransform();
	UMapMeshElements<MeshElementVertex>& getVertices();
	UMapMeshElements<MeshElementEdge>& getEdges();
	UMapMeshElements<MeshElementFace>& getFaces();

	void setTransform(Transform _transform);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};
