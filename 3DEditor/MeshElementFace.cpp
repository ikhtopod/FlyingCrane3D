#include "MeshElementFace.h"


const GLenum MeshElementFace::DEFAULT_MESH_TYPE = GL_LINE_LOOP;

MeshElementFace::MeshElementFace(Face& _face) :
	MeshElementFace(_face.first, _face.second, _face.third) {}

MeshElementFace::MeshElementFace(Vertex& first, Vertex& second, Vertex& third) :
	MeshElement(DEFAULT_MESH_TYPE) {

	this->vertices.insert(this->vertices.end(), { first, second, third });
	this->indices.insert(this->indices.end(), { 0, 1, 2 });
}
