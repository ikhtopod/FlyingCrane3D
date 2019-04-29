#include "Face.h"


Face::Face(Vertex& _first, Vertex& _second, Vertex& _third) :
	first(_first), second(_second), third(_third) {}

bool Face::operator==(const Face& face) const {
	return (this->first == face.first && this->second == face.second && this->third == face.third) ||
		(this->first == face.second && this->second == face.first && this->third == face.third) ||
		(this->first == face.third && this->second == face.second && this->third == face.first) ||
		(this->first == face.first && this->second == face.third && this->third == face.second);
}

