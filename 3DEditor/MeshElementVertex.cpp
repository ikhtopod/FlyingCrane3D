#include "MeshElementVertex.h"


const GLenum MeshElementVertex::DEFAULT_MESH_TYPE = GL_POINTS;

MeshElementVertex::MeshElementVertex(Vertex _vertex) :
	MeshElementVertex(_vertex,
					  Shader {
						  R"(..\resources\shaders\mesh-element-shader.vs)",
						  R"(..\resources\shaders\mesh-element-shader.fs)"
					  }
	) {}

MeshElementVertex::MeshElementVertex(Vertex _vertex, Shader _shader) :
	MeshElement(DEFAULT_MESH_TYPE, _shader), vertex(_vertex) {

	this->count_vertices = 1;
}


void MeshElementVertex::init() {
	glGenVertexArrays(BUFFER_SIZE, &this->vao);
	glGenBuffers(BUFFER_SIZE, &this->vbo);
	glGenBuffers(BUFFER_SIZE, &this->ebo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->count_vertices * sizeof(Vertex), &vertex, GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count_vertices * sizeof(GLuint),
				 &vertex.index, GL_STREAM_DRAW);

	// vertex positions
	glEnableVertexAttribArray(MeshBase::AttribIndex::POSITION);
	glVertexAttribPointer(MeshBase::AttribIndex::POSITION, this->count_vertices,
						  GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glBindVertexArray(0); // unbind

	this->shader.init();
	this->shader.resetLambdaDraw();
}

void MeshElementVertex::draw() {
	this->shader.setParentTransform(this->getGlobalTransform());
	this->shader.draw();

	glBindVertexArray(this->vao);
	glDrawElements(this->type, this->count_vertices, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0); // unbind
}
