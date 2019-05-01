#include "MeshElementVertex.h"


const GLenum MeshElementVertex::DEFAULT_MESH_TYPE = GL_POINTS;

MeshElementVertex::MeshElementVertex(Vertex _vertex, GLuint _vao, GLuint _vbo) :
	MeshElementVertex(_vertex, _vao, _vbo,
					  Shader {
						  R"(..\resources\shaders\mesh-element-shader.vs)",
						  R"(..\resources\shaders\mesh-element-shader.fs)"
					  }
	) {}

MeshElementVertex::MeshElementVertex(Vertex _vertex, GLuint _vao, GLuint _vbo, Shader _shader) :
	MeshElement(DEFAULT_MESH_TYPE, _shader), vertex(_vertex) {

	this->vao = _vao;
	this->vbo = _vbo;
	this->indices.push_back(vertex.index);
}


void MeshElementVertex::init() {
	glGenBuffers(BUFFER_SIZE, &this->ebo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

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

	glBindVertexArray(this->vao);
	glDrawElements(this->type, this->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0); // unbind
}

void MeshElementVertex::free() {
	glDeleteBuffers(BUFFER_SIZE, &this->ebo);

	this->shader.free();
}
