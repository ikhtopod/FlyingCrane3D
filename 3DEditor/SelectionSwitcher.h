#pragma once

#include "Selection.h"
#include "SelectionObject.h"
#include "SelectionElementPoint.h"
#include "SelectionElementEdge.h"
#include "SelectionElementFace.h"

enum class SelectionMode {
	VERTEX, EDGE, FACE,
	OBJECT
};

enum class SelectionActionMode {
	NONE,
	MOVING, ROTATION, SCALING
};

class SelectionSwitcher {
public:
	static const SelectionMode DEFAULT_SELECTION_MODE;

private:
	SelectionMode selectionMode;
	SelectionActionMode actionMode;

	std::unordered_map<SelectionMode, std::shared_ptr<Selection>> selections {};

public:
	SelectionSwitcher();
	~SelectionSwitcher() = default;

	SelectionMode getSelectionMode();
	void setSelectionMode(SelectionMode _mode);
	bool hasSelection(SelectionMode _mode);

	SelectionActionMode getActionMode();
	void setActionMode(SelectionActionMode _actionMode);
	void resetActionMode();

	std::shared_ptr<Selection> getSelection();
	void switchSelectionInput();
	void switchActionInput();
	void mouseActionInput(int button, int action, int mods);

	void clearSelections();
};

