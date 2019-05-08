#pragma once

#include "MeshElement.h"
#include "Vertex.h"
#include "Point.h"

class MeshElementPoint final : public MeshElement {
public:
	static const GLenum DEFAULT_MESH_TYPE;

public:
	MeshElementPoint() = delete;
	MeshElementPoint(Point& _point);
	MeshElementPoint(Vertex& _vertex);
	virtual ~MeshElementPoint() = default;
};
