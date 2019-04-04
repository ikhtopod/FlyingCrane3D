#pragma once

#include "Util.h"
#include "ITriada.h"
#include "Application.h"
#include "Shader.h"

enum class SelectionMode {
	POINT, EDGE, FACE,
	OBJECT
};

enum class SelectionTransformMode {
	NONE,
	MOVE, ROTATE, SCALE
};


class Selection : public ITriada {
private:
	SelectionMode mode;
	SelectionTransformMode transformMode;
	Shader shader;

	std::map<std::string, Object*> selectedObjects {};

private:
	void selectObject();

public:
	Selection();
	~Selection() = default;

	SelectionMode getMode();
	void setMode(SelectionMode _mode);

	SelectionTransformMode getTransformMode();
	void setTransformMode(SelectionTransformMode _transformMode);

public:
	void keyboardInput();

public:
	void select(int button, int action, int mods);

	void moveObject();
	void moveAction();
	void resetTransformAction();
	void transformAction();
	void mouseInput();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
