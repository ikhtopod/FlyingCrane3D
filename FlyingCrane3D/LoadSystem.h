#pragma once

#include "DBConnect.h"

class LoadSystem : public DBConnect {
protected:
	std::string getTransformItemById(std::string colName, uint32_t id);
	std::unordered_map<uint32_t, std::string> getObjectsOfScene(uint32_t sceneId);
	std::unordered_map<uint32_t, std::string> getMeshesOfObject(uint32_t objectId);
	std::map<GLuint, glm::vec3> getPolymeshOfMesh(uint32_t meshId);

public:
	LoadSystem() = delete;
	LoadSystem(std::string _server,
			   std::string _login,
			   std::string _password,
			   std::string _database);
	virtual ~LoadSystem() = default;

	void load(std::string sceneName);
};
