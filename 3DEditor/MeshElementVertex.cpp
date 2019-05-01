#include "MeshElementVertex.h"


const GLenum MeshElementVertex::DEFAULT_MESH_TYPE = GL_POINTS;
const GLfloat MeshElementVertex::DEFAULT_POINT_SIZE = 6;

MeshElementVertex::MeshElementVertex(Vertex _vertex) :
	MeshElement(DEFAULT_MESH_TYPE) {

	this->vertices.push_back(_vertex);
	this->indices.push_back(0);
}
