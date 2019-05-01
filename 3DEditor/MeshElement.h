#pragma once

#include "MeshBase.h"

class MeshElement : public MeshBase {
protected:
	static const std::string ELEMENT_VERTEX_SHADER;
	static const std::string ELEMENT_FRAGMENT_SHADER;

protected:
	MeshElement(GLenum _type);
	MeshElement(GLenum _type, Shader _shader);

	std::vector<Vertex> vertices {};
	std::vector<GLuint> indices {};

public:
	virtual ~MeshElement() = default;

	bool isSelected = false;
};
