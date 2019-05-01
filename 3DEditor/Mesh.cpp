#include "Mesh.h"


const GLenum Mesh::DEFAULT_MESH_TYPE = GL_TRIANGLES;


Mesh::Mesh(PolymeshRepresentation _polymesh)
	: Mesh(_polymesh, Mesh::DEFAULT_MESH_TYPE) {}

Mesh::Mesh(PolymeshRepresentation _polymesh, GLenum _type)
	: Mesh(_polymesh, _type, Shader {}) {}

Mesh::Mesh(PolymeshRepresentation _polymesh, GLenum _type, Shader _shader)
	: MeshBase(_type, _shader), polymesh(_polymesh) {}

PolymeshRepresentation& Mesh::getPolymesh() {
	return this->polymesh;
}

void Mesh::init() {
	glGenVertexArrays(BUFFER_SIZE, &this->vao);
	glGenBuffers(BUFFER_SIZE, &this->vbo);
	glGenBuffers(BUFFER_SIZE, &this->ebo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->polymesh.getVertices().size() * sizeof(Vertex),
				 &(this->polymesh.getVertices())[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->polymesh.getIndicesMesh().size() * sizeof(GLuint),
				 &(this->polymesh.getIndicesMesh())[0], GL_STREAM_DRAW);

	// vertex positions
	glEnableVertexAttribArray(MeshBase::AttribIndex::POSITION);
	glVertexAttribPointer(MeshBase::AttribIndex::POSITION, 3, GL_FLOAT, GL_FALSE,
						  sizeof(Vertex), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(MeshBase::AttribIndex::NORMAL);
	glVertexAttribPointer(MeshBase::AttribIndex::NORMAL, 3, GL_FLOAT, GL_FALSE,
						  sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glBindVertexArray(0); // unbind

	this->shader.init();
}

void Mesh::draw() {
	this->shader.setParentTransform(this->getGlobalTransform());
	this->shader.draw();

	glBindVertexArray(this->vao);
	glDrawElements(this->type, this->polymesh.getIndicesMesh().size(),
				   GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0); // unbind
}
