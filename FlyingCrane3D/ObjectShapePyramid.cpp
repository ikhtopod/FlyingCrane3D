#include "ObjectShapePyramid.h"


ObjectShapePyramid::ObjectShapePyramid() : ObjectShape() {
	PolymeshRepresentation polymesh {
		{
			Vertex{ { 1.0f, 0.0f, -1.0f }, 0 },
			Vertex{ { 1.0f, 0.0f, 1.0f }, 1 },
			Vertex{ { -1.0f, 0.0f, 1.0f }, 2 },
			Vertex{ { -1.0f, 0.0f, -1.0f }, 3 },
			Vertex{ { 0.0f, 2.0f, 0.0f }, 4 },
		},
		{
			1, 3, 0,
			0, 4, 1,
			1, 4, 2,
			2, 4, 3,
			4, 0, 3,
			1, 2, 3,
		}
	};

	Mesh mesh { polymesh, GL_TRIANGLES };
	this->addMesh("mesh_pyramid", mesh);
}
