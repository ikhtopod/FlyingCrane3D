#pragma once

#include "ITriada.h"
#include "Application.h"
#include "Shader.h"
#include "SelectionInfo.h"
#include "Object.h"

class Object;

class ISelection {
protected:
	virtual void select() = 0;

public:
	virtual glm::vec3 getCentroid() = 0;

	virtual void moving() = 0;
	virtual void rotation() = 0;
	virtual void scaling() = 0;
};

class Selection : public ITriada, public ISelection {
protected:
	glm::vec2 prevMousePosition {};
	glm::vec2 diffMousePosition {};

	Shader shader;

	std::map<std::string, Object*> selectedObjects {};

protected:
	bool diffIsZero();

public:
	Selection();
	~Selection() = default;

	std::map<std::string, Object*>& getSelectedObjects();
	bool hasSelectedObject(std::string name);
	bool hasSelectedObjects();
	void clearSelectedObjects();

	void updateMousePosition();
	void updateMousePosition(float currentMouseX, float currentMouseY);

public:
	void mouseButtonInput(int button, int action, int mods);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
