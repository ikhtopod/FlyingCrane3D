#pragma once

#include "MeshBase.h"

class MeshElement : public MeshBase {
protected:
	std::vector<GLuint> indices {};

protected:
	MeshElement(GLenum _type, Shader _shader);

public:
	virtual ~MeshElement() = default;

	bool isSelected = false;
};
