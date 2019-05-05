#include "MeshElementEdge.h"


const GLenum MeshElementEdge::DEFAULT_MESH_TYPE = GL_LINES;

MeshElementEdge::MeshElementEdge(Edge& _edge) :
	MeshElementEdge(_edge.first, _edge.second) {}

MeshElementEdge::MeshElementEdge(Vertex& first, Vertex& second) :
	MeshElement(DEFAULT_MESH_TYPE) {

	this->vertices.insert(this->vertices.end(), { first, second });
	this->indices.insert(this->indices.end(), { 0, 1 });
}
