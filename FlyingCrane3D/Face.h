#pragma once

#include "Vertex.h"

class Face {
public:
	Vertex& first;
	Vertex& second;
	Vertex& third;

	Face() = delete;
	Face(Vertex& _first, Vertex& _second, Vertex& _third);
	~Face() = default;

	bool operator==(const Face& face) const;
};

