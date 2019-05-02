#include "MeshElementEdge.h"


const GLenum MeshElementEdge::DEFAULT_MESH_TYPE = GL_LINES;

MeshElementEdge::MeshElementEdge(Edge _edge) :
	MeshElementEdge(_edge.first, _edge.second) {}

MeshElementEdge::MeshElementEdge(Vertex _vertex0, Vertex _vertex1) :
	MeshElement(DEFAULT_MESH_TYPE) {

	this->vertices.insert(this->vertices.end(), { _vertex0, _vertex1 });
	this->indices.insert(this->indices.end(), { 0, 1 });
}
