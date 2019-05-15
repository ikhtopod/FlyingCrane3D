#include "ObjectShapePlane.h"


ObjectShapePlane::ObjectShapePlane() : ObjectShape() {
	PolymeshRepresentation polymesh {
		{
			Vertex{ { -1.0f, 0.0f, 1.0f }, 0 },
			Vertex{ { 1.0f, 0.0f, 1.0f }, 1 },
			Vertex{ { -1.0f, 0.0f, -1.0f }, 2 },
			Vertex{ { 1.0f, 0.0f, -1.0f }, 3 },
		},
		{
			1, 2, 0,
			1, 3, 2,
		},
	};

	Mesh mesh { polymesh, GL_TRIANGLES };

	this->addMesh("mesh_plane.000", mesh);
}
