#pragma once

#include "MeshElement.h"
#include "Vertex.h"
#include "Face.h"

class MeshElementFace final : public MeshElement {
public:
	static const GLenum DEFAULT_MESH_TYPE;

public:
	MeshElementFace() = delete;
	MeshElementFace(Face _face);
	MeshElementFace(Vertex first, Vertex second, Vertex third);
	virtual ~MeshElementFace() = default;
};

