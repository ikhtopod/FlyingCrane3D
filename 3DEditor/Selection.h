#pragma once

#include "ITriada.h"
#include "Application.h"
#include "Shader.h"
#include "SelectionInfo.h"


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

public:
	Selection();
	~Selection() = default;

	std::map<std::string, Object*>& getSelectedObjects();
	bool hasSelectedObjects(std::string name);
	void clearSelectedObjects();

	void updateMousePosition(float relPosX, float relPosY);

public:
	void mouseButtonInput(int button, int action, int mods);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
