#pragma once

#include "Vertex.h"
#include "Point.h"
#include "Edge.h"
#include "Face.h"

class PolymeshRepresentation final {
private:
	std::vector<Vertex> vertices {};
	std::vector<GLuint> indicesMesh {};

	std::vector<Point> points {};
	std::vector<Edge> edges {};
	std::vector<Face> faces {};

	void updatePoints(Vertex& v1, Vertex& v2, Vertex& v3);
	void updateEdges(Vertex& v1, Vertex& v2, Vertex& v3);
	void updateFaces(Vertex& v1, Vertex& v2, Vertex& v3);

	PolymeshRepresentation() = delete;

public:
	PolymeshRepresentation(std::vector<Vertex> _vertices, std::vector<GLuint> _indices);
	~PolymeshRepresentation() = default;

	std::vector<Vertex>& getVertices();
	std::vector<GLuint>& getIndicesMesh();

	std::vector<Point>& getPoints();
	std::vector<Edge>& getEdges();
	std::vector<Face>& getFaces();

	void update();
};

