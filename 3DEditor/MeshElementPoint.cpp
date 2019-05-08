#include "MeshElementPoint.h"


const GLenum MeshElementPoint::DEFAULT_MESH_TYPE = GL_POINTS;

MeshElementPoint::MeshElementPoint(Point& _point) :
	MeshElementPoint(*_point.first) {}

MeshElementPoint::MeshElementPoint(Vertex& _vertex) :
	MeshElement(DEFAULT_MESH_TYPE) {

	this->vertices.push_back(_vertex);
	this->indices.push_back(0);
}
