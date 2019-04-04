#pragma once

#include "Util.h"
#include "ITriada.h"
#include "Application.h"
#include "Shader.h"

enum class SelectionMode {
	POINT, EDGE, FACE,
	OBJECT
};

class Selection : public ITriada {
public:
	static const SelectionMode DEFAULT_SELECTION_MODE;

private:
	SelectionMode mode;
	Shader shader;

	std::map<std::string, Object*> selectedObjects {};

private:
	void selectObject();

public:
	Selection();
	~Selection() = default;

	SelectionMode getMode();
	void setMode(SelectionMode _mode);

public:
	void changeModeInput();

public:
	void select(int button, int action, int mods);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};
