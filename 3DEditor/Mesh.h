#pragma once

class Mesh {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> faces; // indices class Face
	//std::vector<glm::vec2> textureCoords;
public:
	Mesh();
	~Mesh() = default;
};
