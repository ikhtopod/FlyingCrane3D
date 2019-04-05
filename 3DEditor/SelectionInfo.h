#pragma once

class SelectionInfo {
public:
	bool canSelect = true;
	glm::vec4 colorSelect = glm::vec4 {};

public:
	SelectionInfo() = default;
	~SelectionInfo() = default;

	bool colorSelectEquals(const GLubyte colorUnderCursor[4]);
};
