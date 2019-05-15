#include "ObjectSceneGrid.h"


ObjectSceneGrid::_Cuint ObjectSceneGrid::DEFAULT_WIDTH = 10;
ObjectSceneGrid::_Cuint ObjectSceneGrid::DEFAULT_HEIGHT = ObjectSceneGrid::DEFAULT_WIDTH;
ObjectSceneGrid::_Cuint ObjectSceneGrid::DEFAULT_STEP = 1;


ObjectSceneGrid::ObjectSceneGrid()
	: ObjectSceneGrid(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

ObjectSceneGrid::ObjectSceneGrid(_uint _width, _uint _height)
	: ObjectScene(), width(_width), height(_height), step(DEFAULT_STEP) {

	if (this->width == 0) this->width = DEFAULT_WIDTH;
	if (this->height == 0) this->height = DEFAULT_HEIGHT;

	const float halfWidth = this->width / 2.0f;
	const float halfHeight = this->height / 2.0f;


	std::vector<Vertex> verticesX = {
		{ glm::vec3 { halfWidth + 1.0f, 0.0f, 0.0f }, 0 },
		{ glm::vec3 { -halfWidth, 0.0f, 0.0f }, 1 },
	};
	std::vector<GLuint> indicesX = { 0, 1 };

	std::vector<Vertex> verticesZ = {
		{ glm::vec3 { 0.0f, 0.0f, halfHeight + 1.0f }, 0 },
		{ glm::vec3 { 0.0f, 0.0f, -halfHeight }, 1 },
	};
	std::vector<GLuint> indicesZ = { 0, 1 };

	std::vector<Vertex> verticesGrid {};
	std::vector<GLuint> indicesGrid {};

	_uint stepIndices = 0;
	_Cuint countPointsInLine = 2;

	glm::vec3 point1 { halfWidth + 1.0f, 0.0f, -halfHeight };
	glm::vec3 point2 { halfWidth + 1.0f, 0.0f, halfHeight };
	for (_uint i = 0; i <= this->width; i += this->step, stepIndices += countPointsInLine) {
		point1.x -= 1;
		point2.x -= 1;

		if (point1.x == 0.0f) {
			stepIndices -= countPointsInLine;
			continue;
		}

		verticesGrid.push_back({ point1, stepIndices });
		verticesGrid.push_back({ point2, stepIndices + 1 });

		indicesGrid.push_back(stepIndices);
		indicesGrid.push_back(stepIndices + 1);
	}

	glm::vec3 point3 { -halfWidth, 0.0f, halfHeight + 1.0f };
	glm::vec3 point4 { halfWidth, 0.0f, halfHeight + 1.0f };
	for (_uint i = 0; i <= this->height; i += this->step, stepIndices += countPointsInLine) {
		point3.z -= 1;
		point4.z -= 1;

		if (point3.z == 0.0f) {
			stepIndices -= countPointsInLine;
			continue;
		}

		verticesGrid.push_back({ point3, stepIndices });
		verticesGrid.push_back({ point4, stepIndices + 1 });

		indicesGrid.push_back(stepIndices);
		indicesGrid.push_back(stepIndices + 1);
	}


	FsPath meshXVertex { Shader::SHADER_DIRECTORY + R"(\grid-object-mesh-x.vs)" };
	FsPath meshXFragment { Shader::SHADER_DIRECTORY + R"(\grid-object-mesh-x.fs)" };
	FsPath meshZVertex { Shader::SHADER_DIRECTORY + R"(\grid-object-mesh-z.vs)" };
	FsPath meshZFragment { Shader::SHADER_DIRECTORY + R"(\grid-object-mesh-z.fs)" };
	FsPath meshGridVertex { Shader::SHADER_DIRECTORY + R"(\grid-object-mesh.vs)" };
	FsPath meshGridFragment { Shader::SHADER_DIRECTORY + R"(\grid-object-mesh.fs)" };


	PolymeshRepresentation polymeshX { verticesX, indicesX };
	PolymeshRepresentation polymeshZ { verticesZ, indicesZ };
	PolymeshRepresentation polymeshGrid { verticesGrid, indicesGrid };

	Mesh meshX { polymeshX, GL_LINES, Shader { meshXVertex, meshXFragment } };
	Mesh meshZ { polymeshZ, GL_LINES, Shader { meshZVertex, meshZFragment } };
	Mesh meshGrid { polymeshGrid, GL_LINES, Shader { meshGridVertex, meshGridFragment } };

	meshX.getShader().resetLambdaDraw();
	meshZ.getShader().resetLambdaDraw();
	meshGrid.getShader().resetLambdaDraw();

	this->addMesh("meshX", meshX);
	this->addMesh("meshZ", meshZ);
	this->addMesh("meshGrid", meshGrid);
}
