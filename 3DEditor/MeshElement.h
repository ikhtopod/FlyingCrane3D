#pragma once

#include "MeshBase.h"

class MeshElement : public MeshBase {
protected:
	GLuint count_vertices;

protected:
	MeshElement(GLenum _type, Shader _shader);

public:
	virtual ~MeshElement() = default;
};
