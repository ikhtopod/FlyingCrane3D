#include "MeshElementPoint.h"


const GLenum MeshElementPoint::DEFAULT_MESH_TYPE = GL_POINTS;

MeshElementPoint::MeshElementPoint(Point* _point) :
	MeshElement(DEFAULT_MESH_TYPE), point(_point) {

	this->vertices.push_back(*this->point->first);
	this->indices.push_back(0);
}
