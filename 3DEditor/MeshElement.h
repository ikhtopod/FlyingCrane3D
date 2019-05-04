#pragma once

#include "MeshBase.h"
#include "SelectionInfo.h"

class MeshElement : public MeshBase {
protected:
	static const std::string ELEMENT_VERTEX_SHADER;
	static const std::string ELEMENT_FRAGMENT_SHADER;

protected:
	MeshElement(GLenum _type);
	MeshElement(GLenum _type, Shader _shader);

	std::vector<Vertex> vertices {};
	std::vector<GLuint> indices {};

	SelectionInfo selectionInfo {};

public:
	virtual ~MeshElement() = default;

	SelectionInfo& getSelectionInfo();
	void setSelectionInfo(SelectionInfo _selectionInfo);

	virtual void init() override;
	virtual void draw() override;
};
