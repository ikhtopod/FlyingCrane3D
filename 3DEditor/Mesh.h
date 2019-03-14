#pragma once

#include "Shader.h"
#include "Vertex.h"
#include "Polygon.h"


class Mesh {
private:
	static const GLsizei BUFFER_SIZE;
	static const GLenum DEFAULT_MESH_TYPE;

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

	Transform transform {};
	Shader shader {};

	GLenum type { GL_TRIANGLES };

public:
	Mesh();
	Mesh(GLenum _type);
	Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices);
	Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, GLenum _type);
	~Mesh() = default;

	Transform& getTransform();
	Shader& getShader();
	GLenum getType();

	void setTransform(Transform _transform);
	void setShader(Shader& _shader);
	void setType(GLenum _type);

	void init();
	void draw();
	void free();

};
