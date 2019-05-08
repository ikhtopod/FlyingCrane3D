#pragma once

#include "MeshElement.h"
#include "Vertex.h"
#include "Edge.h"

class MeshElementEdge final : public MeshElement {
public:
	static const GLenum DEFAULT_MESH_TYPE;

	Edge* edge;

public:
	MeshElementEdge() = delete;
	MeshElementEdge(Edge* _edge);
	virtual ~MeshElementEdge() = default;
};

