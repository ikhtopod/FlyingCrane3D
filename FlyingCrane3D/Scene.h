#pragma once

#include "ITriada.h"
#include "Vertex.h"
#include "PolymeshRepresentation.h"
#include "Object.h"
#include "ObjectScene.h"
#include "ObjectSceneGrid.h"
#include "ObjectShape.h"
#include "ObjectShapeCube.h"
#include "Camera.h"
#include "CameraSwitcher.h"
#include "Selection.h"
#include "SelectionSwitcher.h"
#include "Model.h"
#include "Transform.h"
#include "Selection.h"

class Scene final : public ITriada {
private:
	template<class T>
	using MapObject = std::map<std::string, std::shared_ptr<T>>;

	using MapObjectScene = MapObject<ObjectScene>;
	using MapObjectShape = MapObject<ObjectShape>;

private:
	CameraSwitcher cameraSwitcher {};
	SelectionSwitcher selectionSwitcher {};
	Model model {};
	Transform transform {};

private:
	MapObjectScene sceneObjects {};
	MapObjectShape objects {};

	void deleteMarkedObjects();
	void initFill();

public:
	Scene() = default;
	~Scene() = default;

	CameraSwitcher& getCameraSwitcher();
	Camera& getCamera();
	SelectionSwitcher& getSelectionSwitcher();
	Selection& getSelection();
	Model& getModel();
	Transform& getTransform();

	MapObjectShape& getObjects();

	void addSceneObject(std::string _name, ObjectScene _object);

	void addObject(ObjectShape& _object);
	void addObject(ObjectShape&& _object);
	void addObject(const std::string& _name, ObjectShape& _object);
	void addObject(const std::string& _name, ObjectShape&& _object);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
