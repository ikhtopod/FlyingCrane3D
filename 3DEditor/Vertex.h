#pragma once

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;

	Vertex(glm::vec3 _position);
	Vertex(glm::vec3 _position, glm::vec3 _normal);

	bool operator==(const Vertex& v1) const;
};
