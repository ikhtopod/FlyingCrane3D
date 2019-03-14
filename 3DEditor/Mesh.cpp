#include "Mesh.h"


const GLsizei Mesh::BUFFER_SIZE = 1;

Mesh::Mesh() {
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
	: vertices(_vertices), indices(_indices) {}

Mesh::~Mesh() {}


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
}

void Mesh::draw() {
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0); // unbind
}


void Mesh::free() {
	glDeleteVertexArrays(BUFFER_SIZE, &this->vao);
	glDeleteBuffers(BUFFER_SIZE, &this->vbo);
	glDeleteBuffers(BUFFER_SIZE, &this->ebo);
}

