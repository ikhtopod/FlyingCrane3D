#pragma once

#include "ITriada.h"
#include "Vertex.h"
#include "Object.h"
#include "GridObject.h"
#include "Camera.h"
#include "CameraSwitcher.h"
#include "Model.h"
#include "Transform.h"
#include "Selection.h"

class Scene final : public ITriada {
private:
	CameraSwitcher cameraSwitcher {};
	Model model {};
	Transform transform {};
	Selection selection {};

private:
	std::map<std::string, Object> standardObjects {};
	std::map<std::string, Object> objects {};

public:
	Scene() = default;
	~Scene() = default;

	CameraSwitcher& getCameraSwitcher();
	Camera& getCamera();
	Model& getModel();
	Transform& getTransform();
	Selection& getSelection();

	std::map<std::string, Object>& getObjects();

	void addStandardObject(std::string _name, Object _object);
	void addObject(std::string _name, Object _object);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
