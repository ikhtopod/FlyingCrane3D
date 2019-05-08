#pragma once

#include "Vertex.h"

class Edge {
public:
	Vertex& first;
	Vertex& second;

	Edge() = delete;
	Edge(Vertex& _first, Vertex& _second);
	~Edge() = default;

	bool operator==(const Edge& edge) const;
};
