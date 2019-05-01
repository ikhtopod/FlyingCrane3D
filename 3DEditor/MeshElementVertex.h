#pragma once

#include "MeshElement.h"
#include "Vertex.h"

class MeshElementVertex final : public MeshElement {
private:
	static const GLenum DEFAULT_MESH_TYPE;
	static const GLfloat DEFAULT_POINT_SIZE;

private:
	using FsPath = std::filesystem::path;

public:
	MeshElementVertex() = delete;
	MeshElementVertex(Vertex _vertex);
	virtual ~MeshElementVertex() = default;

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};
