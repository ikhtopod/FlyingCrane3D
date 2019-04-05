#pragma once

#include "Util.h"
#include "Selection.h"
#include "Application.h"
#include "Shader.h"
#include "SelectionInfo.h"

class SelectionObject : public Selection {
	virtual void select() override;

	virtual void moving() override;
	virtual void rotation() override;
	virtual void scaling() override;
};

