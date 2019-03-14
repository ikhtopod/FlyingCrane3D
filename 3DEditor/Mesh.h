#pragma once

#include "Vertex.h"
#include "Polygon.h"


class Mesh {
private:
	static const GLsizei BUFFER_SIZE;

	enum AttribIndex : GLuint {
		POSITION,
		// NORMAL,
		// TEXTURE,
		// TANGENT,
		// BITANGENT,
	};

private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

public:
	Mesh();
	Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices);
	~Mesh();

	void init();
	void draw();
	void free();
};
