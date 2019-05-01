#pragma once

#include "ITriada.h"
#include "Shader.h"
#include "Transform.h"

class MeshBase : public ITriada {
protected:
	static const GLsizei BUFFER_SIZE;

	enum AttribIndex : GLuint {
		POSITION, NORMAL
	};

protected:
	GLuint vao, vbo, ebo;

	Transform transform {};
	Transform parentTransform {};
	Transform globalTransform {};

	Shader nativeShader {};
	Shader shader {};

	GLenum type;

	MeshBase();
	MeshBase(GLenum _type, Shader _shader);

public:
	virtual ~MeshBase() = default;

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

	virtual void free() override;
};
