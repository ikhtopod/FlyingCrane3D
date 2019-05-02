#pragma once

#include "MeshElement.h"
#include "Vertex.h"
#include "Edge.h"

class MeshElementEdge final : public MeshElement {
private:
	static const GLenum DEFAULT_MESH_TYPE;
	static const GLfloat DEFAULT_POINT_SIZE;

public:
	MeshElementEdge() = delete;
	MeshElementEdge(Edge _edge);
	MeshElementEdge(Vertex _vertex0, Vertex _vertex1);
	virtual ~MeshElementEdge() = default;
};

