#include "MeshElementVertex.h"


const GLenum MeshElementVertex::DEFAULT_MESH_TYPE = GL_POINTS;
const GLfloat MeshElementVertex::DEFAULT_POINT_SIZE = 6;

MeshElementVertex::MeshElementVertex(Vertex _vertex) :
	MeshElement(DEFAULT_MESH_TYPE) {

	this->vertices.push_back(_vertex);
	this->indices.push_back(0);
}


void MeshElementVertex::init() {
	glGenVertexArrays(BUFFER_SIZE, &this->vao);
	glGenBuffers(BUFFER_SIZE, &this->vbo);
	glGenBuffers(BUFFER_SIZE, &this->ebo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
				 &(this->vertices)[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
				 &(this->indices)[0], GL_STREAM_DRAW);

	// vertex positions
	glEnableVertexAttribArray(MeshBase::AttribIndex::POSITION);
	glVertexAttribPointer(MeshBase::AttribIndex::POSITION, 3,
						  GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glBindVertexArray(0); // unbind

	this->shader.init();
	this->shader.resetLambdaDraw();
}

void MeshElementVertex::draw() {
	this->shader.setParentTransform(this->getGlobalTransform());
	this->shader.draw();

	glPointSize(DEFAULT_POINT_SIZE);
	glBindVertexArray(this->vao);
	glDrawElements(this->type, this->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0); // unbind
	glPointSize(1.0f);
}

void MeshElementVertex::free() {
	glDeleteVertexArrays(BUFFER_SIZE, &this->vao);
	glDeleteBuffers(BUFFER_SIZE, &this->vbo);
	glDeleteBuffers(BUFFER_SIZE, &this->ebo);

	this->shader.free();
}
