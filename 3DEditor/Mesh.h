#pragma once

#include "ITriada.h"
#include "Object.h"
#include "Shader.h"
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"

class Object;

class Mesh : public ITriada {
private:
	static const GLsizei BUFFER_SIZE;
	static const GLenum DEFAULT_MESH_TYPE;

	enum AttribIndex : GLuint {
		POSITION,
		NORMAL,
	};

private:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	std::vector<Vertex> vertices {};
	std::vector<Edge> edges {};
	std::vector<Face> faces {};
	std::vector<GLuint> indices {};

	Transform transform {};
	Transform parentTransform {};
	Transform globalTransform {};
	Shader nativeShader {};
	Shader shader {};

	GLenum type { GL_TRIANGLES };

public:
	Mesh();
	Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, GLenum _type);
	Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, GLenum _type, Shader _shader);
	~Mesh() = default;

	std::vector<Vertex>& getVertices();
	std::vector<Edge>& getEdges();
	std::vector<Face>& getFaces();

	Transform& getTransform();
	Transform& getParentTransform();
	Transform& getGlobalTransform();
	Shader& getShader();
	GLenum getType();

	void setTransform(Transform _transform);
	void setParentTransform(Transform _pTransform);
	void setGlobalTransform(Transform _gTransform);
	void setShader(Shader& _shader);

	void resetShaderToNative();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};

/* Exceptions */

class MeshException : std::exception {
public:
	explicit MeshException(char const* const message);
};

