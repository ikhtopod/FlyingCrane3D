#include "MeshBase.h"

const GLsizei MeshBase::BUFFER_SIZE = 1;


MeshBase::MeshBase() :
	type(GL_TRIANGLES), nativeShader(), shader(nativeShader) {}

MeshBase::MeshBase(GLenum _type, Shader _shader) :
	type(_type), nativeShader(_shader), shader(_shader) {}


Transform& MeshBase::getGlobalTransform() {
	return this->globalTransform;
}

GLuint& MeshBase::getVAO() {
	return this->vao;
}

GLuint& MeshBase::getVBO() {
	return this->vbo;
}

GLuint& MeshBase::getEBO() {
	return this->ebo;
}

Transform& MeshBase::getTransform() {
	return this->transform;
}

Transform& MeshBase::getParentTransform() {
	return this->parentTransform;
}

Shader& MeshBase::getShader() {
	return this->shader;
}

GLenum MeshBase::getType() {
	return this->type;
}


void MeshBase::setGlobalTransform(Transform _gTransform) {
	this->globalTransform = _gTransform;
}

void MeshBase::setTransform(Transform _transform) {
	this->transform = _transform;
	this->setGlobalTransform(this->getParentTransform() + this->getTransform());
}

void MeshBase::setParentTransform(Transform _pTransform) {
	this->parentTransform = _pTransform;
	this->setGlobalTransform(this->getParentTransform() + this->getTransform());
}

void MeshBase::setShader(Shader& _shader) {
	this->shader = _shader;
}

void MeshBase::setType(GLenum _type) {
	this->type = _type;
}


void MeshBase::resetShaderToNative() {
	this->setShader(this->nativeShader);
}

void MeshBase::free() {
	glDeleteVertexArrays(BUFFER_SIZE, &this->vao);
	glDeleteBuffers(BUFFER_SIZE, &this->vbo);
	glDeleteBuffers(BUFFER_SIZE, &this->ebo);

	this->shader.free();
}
