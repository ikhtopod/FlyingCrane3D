#pragma once

#include "ITriada.h"
#include "Object.h"
#include "Shader.h"
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"
#include "PolymeshRepresentation.h"


class Object;

class Mesh final : public ITriada {
private:
	static const GLsizei BUFFER_SIZE;
	static const GLenum DEFAULT_MESH_TYPE;

	enum AttribIndex : GLuint {
		POSITION,
		NORMAL,
	};

private:
	GLuint vao, vbo, ebo;

	PolymeshRepresentation polymesh;

	Transform transform {};
	Transform parentTransform {};
	Transform globalTransform {};

	Shader nativeShader {};
	Shader shader {};

	GLenum type;

	Mesh() = delete;

public:
	Mesh(PolymeshRepresentation _polymesh);
	Mesh(PolymeshRepresentation _polymesh, GLenum _type);
	Mesh(PolymeshRepresentation _polymesh, GLenum _type, Shader _shader);
	~Mesh() = default;

	PolymeshRepresentation& getPolymesh();
	Transform& getTransform();
	Transform& getParentTransform();
	Transform& getGlobalTransform();
	Shader& getShader();
	GLenum getType();

	void setTransform(Transform _transform);
	void setParentTransform(Transform _pTransform);
	void setGlobalTransform(Transform _gTransform);
	void setShader(Shader& _shader);
	void setType(GLenum _type);

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

