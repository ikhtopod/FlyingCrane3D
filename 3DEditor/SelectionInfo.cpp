#include "SelectionInfo.h"

bool SelectionInfo::colorSelectEquals(const GLubyte colorUnderCursor[4]) {
	return this->colorSelect.r == colorUnderCursor[0] &&
		this->colorSelect.g == colorUnderCursor[1] &&
		this->colorSelect.b == colorUnderCursor[2] &&
		this->colorSelect.a == colorUnderCursor[3];
}
