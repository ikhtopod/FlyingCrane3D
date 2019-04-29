#pragma once

#include "Vertex.h"
#include "Edge.h"
#include "Face.h"

class PolymeshRepresentation final {
private:
	std::vector<GLuint> indices {};

	std::vector<Vertex> vertices {};
	std::vector<Edge> edges {};
	std::vector<Face> faces {};

	PolymeshRepresentation() = delete;

public:
	PolymeshRepresentation(std::vector<Vertex> _vertices, std::vector<GLuint> _indices);
	~PolymeshRepresentation() = default;

	std::vector<GLuint>& getIndices();

	std::vector<Vertex>& getVertices();
	std::vector<Edge>& getEdges();
	std::vector<Face>& getFaces();

	void update();
};

