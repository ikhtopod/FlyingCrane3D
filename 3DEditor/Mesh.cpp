#include "Mesh.h"


const GLsizei Mesh::BUFFER_SIZE = 1;
const GLenum Mesh::DEFAULT_MESH_TYPE = GL_TRIANGLES;


Mesh::Mesh() : Mesh(DEFAULT_MESH_TYPE) {}

Mesh::Mesh(GLenum _type) : type(_type) {
	this->vertices = {
		glm::vec3 { 1.0f, 0.0f, -1.0f },
		glm::vec3 { 1.0f, 0.0f, 1.0f },
		glm::vec3 { -1.0f, 0.0f, 1.0f },
		glm::vec3 { -1.0f, 0.0f, -1.0f },
		glm::vec3 { 0.0f, 2.0f, 0.0f },
	};

	this->indices = {
		1, 3, 0,
		0, 4, 1,
		1, 4, 2,
		2, 4, 3,
		4, 0, 3,
		1, 2, 3,
	};
}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices)
	: Mesh(_vertices, _indices, DEFAULT_MESH_TYPE) {}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices, GLenum _type)
	: vertices(_vertices), indices(_indices), type(_type) {}


Transform& Mesh::getTransform() {
	return this->transform;
}

Shader& Mesh::getShader() {
	return this->shader;
}

GLenum Mesh::getType() {
	return this->type;
}

void Mesh::setTransform(Transform _transform) {
	this->transform = _transform;
}


void Mesh::setShader(Shader& _shader) {
	this->shader.free();
	this->shader = _shader;
	this->shader.init();
}

void Mesh::setType(GLenum _type) {}


void Mesh::init() {
	glGenVertexArrays(BUFFER_SIZE, &this->vao);
	glGenBuffers(BUFFER_SIZE, &this->vbo);
	glGenBuffers(BUFFER_SIZE, &this->ebo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &(this->vertices)[0], GL_STREAM_DRAW); // GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &(this->indices)[0], GL_STREAM_DRAW);

	// vertex positions
	glEnableVertexAttribArray(Mesh::AttribIndex::POSITION);
	glVertexAttribPointer(Mesh::AttribIndex::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// vertex normals
	//glEnableVertexAttribArray(Mesh::AttribIndex::NORMAL);
	//glVertexAttribPointer(Mesh::AttribIndex::NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glBindVertexArray(0); // unbind

	this->shader.init();
}


void Mesh::draw() {
	glBindVertexArray(this->vao);
	glDrawElements(this->type, this->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0); // unbind

	this->shader.draw();
}


void Mesh::free() {
	glDeleteVertexArrays(BUFFER_SIZE, &this->vao);
	glDeleteBuffers(BUFFER_SIZE, &this->vbo);
	glDeleteBuffers(BUFFER_SIZE, &this->ebo);

	this->shader.free();
}
