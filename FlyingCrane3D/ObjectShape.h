#pragma once

#include "Object.h"
#include "Mesh.h"


class ObjectShape : public Object {
public:
	Mesh pivotPoint;
	bool canDrawPivotPoint = true;

public:
	ObjectShape();
	virtual ~ObjectShape() = default;

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};
