#pragma once

#include "Selection.h"

class SelectionPoint : public Selection {
	virtual void select() override;

	virtual void moving() override;
	virtual void rotation() override;
	virtual void scaling() override;
};

