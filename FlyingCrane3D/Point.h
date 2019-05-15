#pragma once

#include "Vertex.h"

class Point {
public:
	Vertex& first;

	Point() = delete;
	Point(Vertex& _first);
	~Point() = default;

	bool operator==(const Point& point) const;
};
