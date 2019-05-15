#include "ObjectShapeCube.h"


ObjectShapeCube::ObjectShapeCube() : ObjectShape() {
	std::vector<Vertex> gridVertices {
		Vertex{ { -1.000000f, -1.000000f, 1.000000f } },
		Vertex{ { -1.000000f, 1.000000f, 1.000000f } },
		Vertex{ { -1.000000f, -1.000000f, -1.000000f } },
		Vertex{ { -1.000000f, 1.000000f, -1.000000f } },
		Vertex{ { 1.000000f, -1.000000f, 1.000000f } },
		Vertex{ { 1.000000f, 1.000000f, 1.000000f } },
		Vertex{ { 1.000000f, -1.000000f, -1.000000f } },
		Vertex{ { 1.000000f, 1.000000f, -1.000000f } },
	};

	std::vector<GLuint> gridIndices {
		1, 2, 0,
		3, 6, 2,
		7, 4, 6,
		5, 0, 4,
		6, 0, 2,
		3, 5, 7,
		1, 3, 2,
		3, 7, 6,
		7, 5, 4,
		5, 1, 0,
		6, 4, 0,
		3, 1, 5,
	};

	for (std::size_t i = 0; i < gridVertices.size(); i++) {
		gridVertices[i].index = static_cast<GLuint>(i);
	}

	PolymeshRepresentation polymesh { gridVertices, gridIndices };
	Mesh mesh { polymesh, GL_TRIANGLES };
	this->addMesh("mesh_cube.000", mesh);
}
