#pragma once

#include "ITriada.h"
#include "Util.h"
#include "Application.h"
#include "Shader.h"
#include "SelectionInfo.h"
#include "Object.h"
#include "MeshElementManager.h"

class Object;

class ISelection {
protected:
	virtual void select() = 0;
	virtual std::vector<glm::vec3> getVerticesForCentroid() = 0;

public:
	virtual void moving() = 0;
	virtual void rotation() = 0;
	virtual void scaling() = 0;
};

class Selection : public ITriada, public ISelection {
public:
	static const glm::vec4 CLEAR_COLOR;

protected:
	glm::vec2 prevMousePosition {};
	glm::vec2 diffMousePosition {};

	Shader shader;

	std::map<std::string, Object*> selectedObjects {};

protected:
	bool diffIsZero();

	void clearColor();

public:
	Selection();
	~Selection() = default;

	std::map<std::string, Object*>& getSelectedObjects();
	bool hasSelectedObject(std::string name);
	bool hasSelectedObjects();
	void clearSelectedObjects();

	void updateMousePosition();
	void updateMousePosition(float currentMouseX, float currentMouseY);

	glm::vec3 getCentroid();

public:
	void mouseButtonInput(int button, int action, int mods);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
