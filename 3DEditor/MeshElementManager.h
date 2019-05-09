#pragma once

#include "ITriada.h"
#include "Transform.h"
#include "Vertex.h"
#include "Point.h"
#include "Edge.h"
#include "Face.h"
#include "Object.h"
#include "Mesh.h"
#include "MeshElement.h"
#include "MeshElementPoint.h"
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
	UMapMeshElements<MeshElementPoint> points {};
	UMapMeshElements<MeshElementEdge> edges {};
	UMapMeshElements<MeshElementFace> faces {};

	SelectionMode currentSelectionMode = SelectionMode::OBJECT;

	Transform transform {};
	Object* parent = nullptr;

public:
	MeshElementManager() = default;
	MeshElementManager(Object* _parent);
	~MeshElementManager() = default;

private:
	void updateSelectionMode();

	void updatePoints();
	void updateEdges();
	void updateFaces();

public:
	void update();

	UMapMeshElements<MeshElementPoint>& getPoints();
	UMapMeshElements<MeshElementEdge>& getEdges();
	UMapMeshElements<MeshElementFace>& getFaces();

	Transform& getTransform();
	Object* getParent();

	void setTransform(Transform _transform);
	void setParent(Object* _parent);
	
	bool hasParent();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};
