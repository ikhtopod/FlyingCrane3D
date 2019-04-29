#include "Edge.h"

Edge::Edge(Vertex& _first, Vertex& _second)
	: first(_first), second(_second) {}

bool Edge::operator==(const Edge& edge) const {
	return (this->first == edge.first && this->second == edge.second) ||
		(this->first == edge.second && this->second == edge.first);
}
