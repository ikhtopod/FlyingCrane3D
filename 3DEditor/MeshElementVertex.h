#pragma once

#include "MeshElement.h"
#include "Vertex.h"

class MeshElementVertex final : public MeshElement {
private:
	static const GLenum DEFAULT_MESH_TYPE;

public:
	MeshElementVertex() = delete;
	MeshElementVertex(Vertex _vertex);
	virtual ~MeshElementVertex() = default;
};
