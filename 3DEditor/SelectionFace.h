#pragma once

#include "Selection.h"

class SelectionFace : public Selection {
	virtual void select() override;

	virtual void moving() override;
	virtual void rotation() override;
	virtual void scaling() override;
};

