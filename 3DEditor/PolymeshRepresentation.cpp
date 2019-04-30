#include "PolymeshRepresentation.h"


PolymeshRepresentation::PolymeshRepresentation(
	std::vector<Vertex> _vertices, std::vector<GLuint> _indices)
	: vertices(_vertices), indicesMesh(_indices) {

	this->update();
}

std::vector<GLuint>& PolymeshRepresentation::getIndicesMesh() {
	return this->indicesMesh;
}

std::vector<Vertex>& PolymeshRepresentation::getVertices() {
	return this->vertices;
}

std::vector<Edge>& PolymeshRepresentation::getEdges() {
	return this->edges;
}

std::vector<Face>& PolymeshRepresentation::getFaces() {
	return this->faces;
}

void PolymeshRepresentation::update() {
	for (std::size_t i = 0; i < this->indicesMesh.size(); i += 3) {
		Vertex& v1 = this->vertices[this->indicesMesh[i]];
		Vertex& v2 = (i + 1) < this->indicesMesh.size() ?
			this->vertices[this->indicesMesh[i + 1]] : this->vertices[this->indicesMesh[i]];
		Vertex& v3 = (i + 2) < this->indicesMesh.size() ?
			this->vertices[this->indicesMesh[i + 2]] : this->vertices[this->indicesMesh[i + 1]];

		// list unique faces
		Face face { v1, v2, v3 };
		auto pred_f = [&face](const Face& f) {
			return (face == f);
		};

		if (std::find_if(this->faces.begin(), this->faces.end(), pred_f) == this->faces.end()) {
			this->faces.push_back(face);
		}//fi

		// list unique edges
		for (Edge edge : { Edge { v1, v2 }, Edge { v2, v3 }, Edge { v3, v1 } }) {
			auto pred_e = [&edge](const Edge& e) {
				return (edge == e);
			};

			if (std::find_if(this->edges.begin(), this->edges.end(), pred_e) == this->edges.end()) {
				this->edges.push_back(edge);
			}//fi
		}//rof
	}//rof
}
