#pragma once

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;

	GLuint index;

	Vertex(glm::vec3 _position, GLuint _index);
	Vertex(glm::vec3 _position, glm::vec3 _normal, GLuint _index);

	bool operator==(const Vertex& v1) const;
};
