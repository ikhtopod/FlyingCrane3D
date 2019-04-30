#pragma once

#include "MeshBase.h"

class MeshElement : public MeshBase {
public:
	MeshElement() = delete;
	MeshElement(GLenum _type, Shader _shader);
	virtual ~MeshElement() = default;
};
