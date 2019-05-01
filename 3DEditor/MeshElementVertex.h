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
	MeshElementVertex(Vertex _vertex, GLuint _vao, GLuint _vbo);
	MeshElementVertex(Vertex _vertex, GLuint _vao, GLuint _vbo, Shader _shader);
	virtual ~MeshElementVertex() = default;

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};
