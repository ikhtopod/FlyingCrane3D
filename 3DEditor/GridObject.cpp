#include "GridObject.h"


const unsigned int GridObject::DEFAULT_WIDTH = 16;
const unsigned int GridObject::DEFAULT_HEIGHT = GridObject::DEFAULT_WIDTH;
const unsigned int GridObject::DEFAULT_STEP = 1;


GridObject::GridObject()
	: GridObject(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_STEP) {}

GridObject::GridObject(unsigned int _width, unsigned int _height, unsigned int _step)
	: Object(), width(_width), height(_height), step(_step) {

	std::vector<Vertex> verticesZ = {
		glm::vec3 { 0.0f, 0.0f, 5.0f },
		glm::vec3 { 0.0f, 0.0f, -5.0f },
	};
	std::vector<GLuint> indicesZ = { 0, 1 };

	std::vector<Vertex> verticesX = {
		glm::vec3 { 5.0f, 0.0f, 0.0f },
		glm::vec3 { -5.0f, 0.0f, 0.0f },
	};
	std::vector<GLuint> indicesX = { 0, 1 };

	std::vector<Vertex> verticesGrid {};
	std::vector<GLuint> indicesGrid {};

	glm::vec3 point1 { 6.0f, 0.0f, -5.0f };
	glm::vec3 point2 { 6.0f, 0.0f, 5.0f };
	unsigned int num = 0;
	for (unsigned int i = 0; i <= 10; i++, num += 2) {
		point1.x -= 1;
		point2.x -= 1;

		if (point1.x == 0) {
			num -= 2;
			continue;
		}

		verticesGrid.push_back(point1);
		verticesGrid.push_back(point2);

		indicesGrid.push_back(num);
		indicesGrid.push_back(num + 1);
	}

	glm::vec3 point3 { -5.0f, 0.0f, 6.0f };
	glm::vec3 point4 { 5.0f, 0.0f, 6.0f };
	for (unsigned int i = 0; i <= 10; i++, num += 2) {
		point3.z -= 1;
		point4.z -= 1;

		if (point3.z == 0) {
			num -= 2;
			continue;
		}

		verticesGrid.push_back(point3);
		verticesGrid.push_back(point4);

		indicesGrid.push_back(num);
		indicesGrid.push_back(num + 1);
	}


	std::filesystem::path meshXVertex { Util::SHADER_DIRECTORY + R"(\GridObjectMeshX.vs)" };
	std::filesystem::path meshXFragment { Util::SHADER_DIRECTORY + R"(\GridObjectMeshX.fs)" };
	std::filesystem::path meshZVertex { Util::SHADER_DIRECTORY + R"(\GridObjectMeshZ.vs)" };
	std::filesystem::path meshZFragment { Util::SHADER_DIRECTORY + R"(\GridObjectMeshZ.fs)" };
	std::filesystem::path meshGridVertex { Util::SHADER_DIRECTORY + R"(\GridObjectMeshGrid.vs)" };
	std::filesystem::path meshGridFragment { Util::SHADER_DIRECTORY + R"(\GridObjectMeshGrid.fs)" };

	Mesh meshX { verticesX, indicesX, GL_LINES, Shader { meshXVertex, meshXFragment } };
	Mesh meshZ { verticesZ, indicesZ, GL_LINES, Shader { meshZVertex, meshZFragment } };
	Mesh meshGrid { verticesGrid, indicesGrid, GL_LINES, Shader { meshGridVertex, meshGridFragment } };

	this->addMesh("meshX", meshX);
	this->addMesh("meshZ", meshZ);
	this->addMesh("meshGrid", meshGrid);
}

