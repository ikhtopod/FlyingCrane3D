#pragma once

#include "MeshElement.h"
#include "Vertex.h"
#include "Edge.h"

class MeshElementEdge final : public MeshElement {
public:
	static const GLenum DEFAULT_MESH_TYPE;

public:
	MeshElementEdge() = delete;
	MeshElementEdge(Edge _edge);
	MeshElementEdge(Vertex first, Vertex second);
	virtual ~MeshElementEdge() = default;
};

