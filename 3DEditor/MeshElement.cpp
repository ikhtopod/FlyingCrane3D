#include "MeshElement.h"

const std::string MeshElement::ELEMENT_VERTEX_SHADER =
R"(..\resources\shaders\mesh-element-shader.vs)";

const std::string MeshElement::ELEMENT_FRAGMENT_SHADER =
R"(..\resources\shaders\mesh-element-shader.fs)";


MeshElement::MeshElement(GLenum _type) :
	MeshElement(_type,
				Shader {
					ELEMENT_VERTEX_SHADER,
					ELEMENT_FRAGMENT_SHADER
				}
	) {}


MeshElement::MeshElement(GLenum _type, Shader _shader) :
	MeshBase(_type, _shader) {}


void MeshElement::init() {
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

void MeshElement::draw() {
	this->shader.setParentTransform(this->getGlobalTransform());
	this->shader.draw();

	glBindVertexArray(this->vao);
	glDrawElements(this->type, this->indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0); // unbind
}
