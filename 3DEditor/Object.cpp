#include "Object.h"


const GLsizei Object::BUFFER_SIZE = 1;


Object::Object(std::string _name) : name(_name) {}


std::string Object::getName() {
	return this->name;
}

void Object::setName(std::string _name) {
	this->name = _name;
}

void Object::init() {
	glGenVertexArrays(BUFFER_SIZE, &this->vao);
	glGenBuffers(BUFFER_SIZE, &this->vbo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW); // GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW

	glVertexAttribPointer(Object::AttribIndex::POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(Object::AttribIndex::POSITION);

	// texture coord attribute
	// ...

	// shader init
	this->shader.init();
}

void Object::draw() {
	// draw texture
	// ...

	// draw shader
	this->shader.draw();

	// draw mesh
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Object::free() {
	this->shader.free();

	glDeleteVertexArrays(BUFFER_SIZE, &this->vao);
	glDeleteBuffers(BUFFER_SIZE, &this->vbo);
}
