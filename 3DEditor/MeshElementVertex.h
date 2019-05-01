#pragma once

#include "MeshElement.h"
#include "Vertex.h"

class MeshElementVertex final : public MeshElement {
private:
	static const GLenum DEFAULT_MESH_TYPE;

private:
	using FsPath = std::filesystem::path;
	Vertex vertex;

public:
	MeshElementVertex() = delete;
	MeshElementVertex(Vertex _vertex);
	MeshElementVertex(Vertex _vertex, Shader _shader);
	virtual ~MeshElementVertex() = default;

	virtual void init() override;
	virtual void draw() override;
};
