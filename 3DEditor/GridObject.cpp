#include "GridObject.h"


const unsigned int GridObject::DEFAULT_WIDTH = 16;
const unsigned int GridObject::DEFAULT_HEIGHT = GridObject::DEFAULT_WIDTH;
const unsigned int GridObject::DEFAULT_STEP = 1;


GridObject::GridObject(std::string _name)
	: GridObject(_name, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_STEP) {}

GridObject::GridObject(std::string _name, unsigned int _width, unsigned int _height, unsigned int _step)
	: Object(_name), width(_width), height(_height), step(_step) {

	std::vector<Vertex> verticesZ = {
		glm::vec3 { 0.0f, 0.0f, 5.0f },
		glm::vec3 { 0.0f, 0.0f, -5.0f },
	};
	std::vector<Vertex> verticesX = {
		glm::vec3 { 5.0f, 0.0f, 0.0f },
		glm::vec3 { -5.0f, 0.0f, 0.0f },
	};

	std::vector<GLuint> indicesZ = { 1, 2 };
	std::vector<GLuint> indicesX = { 1, 2 };


	Mesh meshX { verticesX, indicesX, GL_LINES };
	Mesh meshZ { verticesZ, indicesZ, GL_LINES };
	//Mesh meshGrid { GL_LINES };

	this->meshes.push_back(meshX);
	this->meshes.push_back(meshZ);
}

