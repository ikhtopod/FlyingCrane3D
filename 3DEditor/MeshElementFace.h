#pragma once

#include "MeshElement.h"
#include "Vertex.h"
#include "Face.h"

class MeshElementFace final : public MeshElement {
public:
	static const GLenum DEFAULT_MESH_TYPE;

private:
	std::vector<Vertex> markPoints {};
	GLuint vaoMark, vboMark;

	void initMark();
	void drawMark();
	void freeMark();

public:
	MeshElementFace() = delete;
	MeshElementFace(Face& _face);
	MeshElementFace(Vertex& first, Vertex& second, Vertex& third);
	virtual ~MeshElementFace() = default;

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;
};

