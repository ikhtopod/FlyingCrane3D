#pragma once

enum class SelectionMode {
	POINT, EDGE, FACE,
	OBJECT
};

class Selection {
public:
	static const SelectionMode DEFAULT_SELECTION_MODE;

private:
	SelectionMode mode;

public:
	Selection();
	~Selection() = default;

	SelectionMode getMode();
	void setMode(SelectionMode _mode);

	void changeModeInput();
};

