#include "Edge.h"

Point::Point(Vertex& _first) : first(_first) {}

bool Point::operator==(const Point& point) const {
	return this->first == point.first;
}
