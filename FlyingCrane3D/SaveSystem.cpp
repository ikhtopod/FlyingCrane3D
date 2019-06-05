#include "SaveSystem.h"


SaveSystem::SaveSystem(std::string _server, std::string _login,
					   std::string _password, std::string _database) :
	DBConnect(_server, _login, _password, _database) {}


uint32_t SaveSystem::getFreeRow(std::string tableName, std::string colIdName) {
	if (this->isConnectionError()) return 1;

	uint32_t freeRow = 1;

	MYSQL_RES *res;
	MYSQL_ROW row;

	std::stringstream req {};
	req << "select " << colIdName << " from " << tableName <<
		" order by " << colIdName;

	this->query(req.str());

	if (res = mysql_store_result(this->connection)) {
		while (row = mysql_fetch_row(res)) {
			if (row[0] != nullptr) {
				if (std::stoul(std::string { row[0] }) > freeRow) {
					break;
				}//fi
			}//fi

			freeRow++;
		}//elihw
	} else {
		std::cout << mysql_error(this->connection) << std::endl;
	}//fi

	return freeRow;
}


void SaveSystem::save(std::string sceneName, std::string categoryName) {
	if (this->isConnectionError()) return;

	Application* appThis = Application::getInstancePtr();

	// заполнить таблицу scenes
	int32_t sceneId = this->getFreeRow("scenes", "id");
	int32_t categoryId = this->getIdByName("categories", "id", categoryName);

	std::stringstream addSceneReq {};
	addSceneReq << "insert into scenes (id, name, category_id) values " <<
		"(" << sceneId << ", '" << sceneName << "', " << categoryId << ")";

	if (this->query(addSceneReq.str()) != 0) {
		std::cout << mysql_error(this->connection) << std::endl;
		return;
	}//fi

	for (auto&[objectName, objectShape] : appThis->getScene().getObjects()) {
		// заполнить таблицу objects
		int32_t objectId = this->getFreeRow("objects", "id");

		std::stringstream addObjectReq {};
		addObjectReq << "insert into objects (id, name, scene_id) values " <<
			"(" << objectId << ", '" << objectName << "', " << sceneId << ")";

		if (this->query(addObjectReq.str()) != 0) {
			std::cout << mysql_error(this->connection) << std::endl;
			return;
		}//fi

		// заполнить таблицу transforms
		std::stringstream addTransformReq {};
		addTransformReq << "insert into transforms (id, position, rotation, scale) values " <<
			"(" << objectId << ", '" <<
			vectorToString(objectShape->getTransform().getPosition()) << "', '" <<
			vectorToString(objectShape->getTransform().getRotation()) << "', '" <<
			vectorToString(objectShape->getTransform().getScale()) << "')";

		if (this->query(addTransformReq.str()) != 0) {
			std::cout << mysql_error(this->connection) << std::endl;
			return;
		}//fi

		for (auto&[meshName, mesh] : objectShape->getMeshes()) {
			// заполнить таблицу meshes
			int32_t meshId = this->getFreeRow("meshes", "id");

			std::stringstream addMeshReq {};
			addMeshReq << "insert into meshes (id, name, `object_id`) values " <<
				"(" << meshId << ", '" << meshName << "', " << objectId << ")";

			if (this->query(addMeshReq.str()) != 0) {
				std::cout << mysql_error(this->connection) << std::endl;
				return;
			}//fi

			// заполнить таблицу polymeshes
			for (Vertex& vertex : mesh.getPolymesh().getVertices()) {
				std::stringstream addPolymeshReq {};
				addPolymeshReq << "insert into polymeshes (id, `index`, vertex, normal) values " <<
					"(" << meshId << ", " << vertex.index << ", '" <<
					vectorToString(vertex.position) << "', '" <<
					vectorToString(vertex.normal) << "')";

				if (this->query(addPolymeshReq.str()) != 0) {
					std::cout << mysql_error(this->connection) << std::endl;
					return;
				}//fi
			}//rof polymesh
		}//rof mesh
	}//rof object
}
