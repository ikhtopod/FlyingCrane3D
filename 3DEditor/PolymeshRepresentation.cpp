#include "PolymeshRepresentation.h"


PolymeshRepresentation::PolymeshRepresentation(
	std::vector<Vertex> _vertices, std::vector<GLuint> _indices)
	: vertices(_vertices), indices(_indices) {
	
	this->update();
}

std::vector<GLuint>& PolymeshRepresentation::getIndices() {
	return this->indices;
}

std::vector<Vertex>& PolymeshRepresentation::getVertices() {
	return this->vertices;
}

std::vector<Edge>& PolymeshRepresentation::getEdges() {
	return this->edges;
}

std::vector<Face>& PolymeshRepresentation::getFaces() {
	return this->faces;
}

void PolymeshRepresentation::update() {
	/* dummy */
}
