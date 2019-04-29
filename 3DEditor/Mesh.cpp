#include "Mesh.h"


const GLsizei Mesh::BUFFER_SIZE = 1;
const GLenum Mesh::DEFAULT_MESH_TYPE = GL_TRIANGLES;


Mesh::Mesh(PolymeshRepresentation _polymesh)
	: Mesh(_polymesh, Mesh::DEFAULT_MESH_TYPE) {}

Mesh::Mesh(PolymeshRepresentation _polymesh, GLenum _type)
	: Mesh(_polymesh, _type, Shader {}) {}

Mesh::Mesh(PolymeshRepresentation _polymesh, GLenum _type, Shader _shader)
	: polymesh(_polymesh), type(_type), 
	nativeShader(_shader), shader(nativeShader) {}


Transform& Mesh::getGlobalTransform() {
	return this->globalTransform;
}

PolymeshRepresentation& Mesh::getPolymesh() {
	return this->polymesh;
}

Transform& Mesh::getTransform() {
	return this->transform;
}

Transform& Mesh::getParentTransform() {
	return this->parentTransform;
}

Shader& Mesh::getShader() {
	return this->shader;
}

GLenum Mesh::getType() {
	return this->type;
}

void Mesh::setGlobalTransform(Transform _gTransform) {
	this->globalTransform = _gTransform;
}

void Mesh::setTransform(Transform _transform) {
	this->transform = _transform;
	this->setGlobalTransform(this->getParentTransform() + this->getTransform());
}

void Mesh::setParentTransform(Transform _pTransform) {
	this->parentTransform = _pTransform;
	this->setGlobalTransform(this->getParentTransform() + this->getTransform());
}


void Mesh::setShader(Shader& _shader) {
	//this->shader.free();
	this->shader = _shader;
	//this->shader.init();
}

void Mesh::setType(GLenum _type) {
	this->type = _type;
}

void Mesh::resetShaderToNative() {
	this->setShader(this->nativeShader);
}


void Mesh::init() {
	glGenVertexArrays(BUFFER_SIZE, &this->vao);
	glGenBuffers(BUFFER_SIZE, &this->vbo);
	glGenBuffers(BUFFER_SIZE, &this->ebo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->polymesh.getVertices().size() * sizeof(Vertex), &(this->polymesh.getVertices())[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->polymesh.getIndices().size() * sizeof(GLuint), &(this->polymesh.getIndices())[0], GL_STREAM_DRAW);

	// vertex positions
	glEnableVertexAttribArray(Mesh::AttribIndex::POSITION);
	glVertexAttribPointer(Mesh::AttribIndex::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(Mesh::AttribIndex::NORMAL);
	glVertexAttribPointer(Mesh::AttribIndex::NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glBindVertexArray(0); // unbind

	this->shader.init();
}


void Mesh::draw() {
	this->shader.setParentTransform(this->getGlobalTransform());
	this->shader.draw();

	glBindVertexArray(this->vao);
	glDrawElements(this->type, this->polymesh.getIndices().size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0); // unbind
}


void Mesh::free() {
	glDeleteVertexArrays(BUFFER_SIZE, &this->vao);
	glDeleteBuffers(BUFFER_SIZE, &this->vbo);
	glDeleteBuffers(BUFFER_SIZE, &this->ebo);

	this->shader.free();
}

/* Exceptions */

MeshException::MeshException(char const* const message)
	: std::exception(message) {}
