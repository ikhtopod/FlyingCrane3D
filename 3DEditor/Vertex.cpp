#include "Vertex.h"

Vertex::Vertex(glm::vec3 _position, GLuint _index)
	: Vertex(_position, { 0.0f, 1.0f, 0.0f }, _index) {}

Vertex::Vertex(glm::vec3 _position, glm::vec3 _normal, GLuint _index) :
	position(_position), normal(_normal), index(_index) {}

bool Vertex::operator==(const Vertex& v1) const {
	return this->position == v1.position && this->normal == v1.normal;
}
