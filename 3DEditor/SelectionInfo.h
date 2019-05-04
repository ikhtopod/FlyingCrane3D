#pragma once

class SelectionInfo {
public:
	bool canSelect = true;
	bool isSelected = false;
	bool isSelectionProcess = false;

	glm::vec4 colorSelect = glm::vec4 {};

public:
	SelectionInfo() = default;
	~SelectionInfo() = default;

	bool colorSelectEquals(const GLubyte colorUnderCursor[4]);
	bool colorSelectEquals(const glm::vec4& colorUnderCursor);
};
