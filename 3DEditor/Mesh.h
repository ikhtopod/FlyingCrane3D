#pragma once

#include "ITriada.h"
#include "Object.h"
#include "Shader.h"
#include "Vertex.h"

class Object;

class Mesh : public ITriada {
private:
	static const GLsizei BUFFER_SIZE;
	static const GLenum DEFAULT_MESH_TYPE;

	enum AttribIndex : GLuint {
		POSITION,
		NORMAL,
		// TEXTURE,
		// TANGENT,
		// BITANGENT,
	};

private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	std::vector<Vertex> vertices {};
	std::vector<GLuint> indices {};

	Transform transform {};
	Transform globalTransform {};
	Shader shader {};

	GLenum type { GL_TRIANGLES };

public:
	Mesh();
	Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, GLenum _type);
	Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, GLenum _type, Shader _shader);
	~Mesh() = default;

	Transform& getTransform();
	Shader& getShader();
	GLenum getType();

	void setTransform(Transform _transform);
	void setShader(Shader& _shader);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};

/* Exceptions */

class MeshException : std::exception {
public:
	explicit MeshException(char const* const message);
};

