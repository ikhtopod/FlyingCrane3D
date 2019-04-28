#pragma once

#include "Vertex.h"

class Edge {
private:
	Vertex* first;
	Vertex* second;

	Edge() = delete;
public:
	Edge(Vertex* _first, Vertex* _second);
	~Edge() = default;
};
