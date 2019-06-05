#include "LoadSystem.h"


LoadSystem::LoadSystem(std::string _server, std::string _login,
					   std::string _password, std::string _database) :
	DBConnect(_server, _login, _password, _database) {}


std::string LoadSystem::getTransformItemById(std::string colName, uint32_t id) {
	if (this->isConnectionError()) return {};

	std::string item { "0.0;0.0;0.0" };

	MYSQL_RES *res;
	MYSQL_ROW row;

	std::stringstream req {};
	req << "select " << colName << " from transforms where id = " << id;

	this->query(req.str());

	if (res = mysql_store_result(this->connection)) {
		if (row = mysql_fetch_row(res)) {
			if (row[0] != nullptr) {
				item = std::string { row[0] };
			}//fi
		}//fi
	} else {
		std::cout << mysql_error(this->connection) << std::endl;
	}//fi

	return item;
}

std::unordered_map<uint32_t, std::string>
LoadSystem::getObjectsOfScene(uint32_t sceneId) {
	if (this->isConnectionError()) return {};

	std::unordered_map<uint32_t, std::string> result {};

	MYSQL_RES *res;
	MYSQL_ROW row;

	std::stringstream addObjectReq {};
	addObjectReq << "select id, name from objects where scene_id = " << sceneId;

	this->query(addObjectReq.str());

	if (res = mysql_store_result(this->connection)) {
		while (row = mysql_fetch_row(res)) {
			if (row[0] != nullptr && row[1] != nullptr) {
				result.insert({ std::stoul(row[0]), std::string { row[1] } });
			}//fi
		}//elihw
	} else {
		std::cout << mysql_error(this->connection) << std::endl;
	}//fi

	return result;
}

std::unordered_map<uint32_t, std::string>
LoadSystem::getMeshesOfObject(uint32_t objectId) {
	if (this->isConnectionError()) return {};

	std::unordered_map<uint32_t, std::string> result {};

	MYSQL_RES *res;
	MYSQL_ROW row;

	std::stringstream addObjectReq {};
	addObjectReq << "select id, name from meshes where `object_id` = " << objectId;

	this->query(addObjectReq.str());

	if (res = mysql_store_result(this->connection)) {
		while (row = mysql_fetch_row(res)) {
			if (row[0] != nullptr && row[1] != nullptr) {
				result.insert({ std::stoul(row[0]), std::string { row[1] } });
			}//fi
		}//elihw
	} else {
		std::cout << mysql_error(this->connection) << std::endl;
	}//fi

	return result;
}

std::map<GLuint, glm::vec3>
LoadSystem::getPolymeshOfMesh(uint32_t meshId) {
	if (this->isConnectionError()) return {};

	std::map<GLuint, glm::vec3> result {};

	MYSQL_RES *res;
	MYSQL_ROW row;

	std::stringstream addObjectReq {};
	addObjectReq << "select `index`, vertex " <<
		"from polymeshes where id = " << meshId;

	this->query(addObjectReq.str());

	if (res = mysql_store_result(this->connection)) {
		while (row = mysql_fetch_row(res)) {
			if (row[0] != nullptr && row[1] != nullptr) {
				result.insert({ std::stoul(row[0]), stringToVector(row[1]) });
			}//fi
		}//elihw
	} else {
		std::cout << mysql_error(this->connection) << std::endl;
	}//fi

	return result;
}

void LoadSystem::load(std::string sceneName) {
	if (this->isConnectionError()) return;

	Application* appThis = Application::getInstancePtr();

	// create scene
	Scene loadScene {};
	appThis->setScene(loadScene);

	uint32_t sceneId = this->getIdByName("scenes", "id", sceneName);

	// get list objects
	for (auto&[objectId, objectName] : this->getObjectsOfScene(sceneId)) {
		ObjectShape object {};

		// get transform of object
		Transform t {};
		t.setPosition(stringToVector(getTransformItemById("position", objectId)));
		t.setRotation(stringToVector(getTransformItemById("rotation", objectId)));
		t.setScale(stringToVector(getTransformItemById("scale", objectId)));
		object.setTransform(t);

		// get list meshes
		for (auto&[meshId, meshName] : this->getMeshesOfObject(objectId)) {
			std::vector<Vertex> vertices {};
			std::vector<GLuint> indices {};

			// get polymesh of mesh
			for (auto&[order, vertex] : this->getPolymeshOfMesh(meshId)) {
				Vertex v { vertex };
				v.index = order;
				vertices.push_back(v);
				indices.push_back(order);
			}//rof polymesh

			PolymeshRepresentation polymesh { vertices, indices };
			Mesh mesh { polymesh };
			object.addMesh(meshName, mesh);
		}//rof meshes

		appThis->getScene().addObject(objectName, object);
	}//rof objects
}
