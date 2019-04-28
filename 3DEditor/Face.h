#pragma once

#include "Edge.h"

class Face {
private:
	Edge* first;
	Edge* second;
	Edge* third;

	Face() = delete;

public:
	Face(Edge* _first, Edge* _second, Edge* _third);
	~Face() = default;
};

