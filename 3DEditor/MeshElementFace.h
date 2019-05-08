#pragma once

#include "MeshElement.h"
#include "Vertex.h"
#include "Face.h"

class MeshElementFace final : public MeshElement {
public:
	static const GLenum DEFAULT_MESH_TYPE;

	Face* face;

private:
	std::vector<Vertex> markPoints {};
	GLuint vaoMark, vboMark;

	void updateMarkList();

	void initMark();
	void drawMark();
	void freeMark();

public:
	MeshElementFace() = delete;
	MeshElementFace(Face* _face);
	virtual ~MeshElementFace() = default;

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};

