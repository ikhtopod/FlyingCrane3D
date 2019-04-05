#pragma once

#include "ITriada.h"
#include "Selection.h"
#include "SelectionObject.h"
#include "SelectionPoint.h"
#include "SelectionEdge.h"
#include "SelectionFace.h"

enum class SelectionMode {
	POINT, EDGE, FACE,
	OBJECT
};

class SelectionSwitcher : public ITriada {
public:
	static const SelectionMode DEFAULT_SELECTION_MODE;

private:
	SelectionMode mode;

	std::unordered_map<SelectionMode, std::shared_ptr<Selection>> selections {};

public:
	SelectionSwitcher();
	~SelectionSwitcher() = default;

	SelectionMode getMode();
	void setMode(SelectionMode _mode);

	bool hasSelection(SelectionMode _mode);

	std::shared_ptr<Selection> getSelection();
	void switchSelectionInput();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};

