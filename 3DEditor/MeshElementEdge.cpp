#include "MeshElementEdge.h"


const GLenum MeshElementEdge::DEFAULT_MESH_TYPE = GL_LINES;

MeshElementEdge::MeshElementEdge(Edge* _edge) :
	MeshElement(DEFAULT_MESH_TYPE), edge(_edge) {

	this->vertices.insert(this->vertices.end(),
						  { *this->edge->first, *this->edge->second });
	this->indices.insert(this->indices.end(), { 0, 1 });
}
