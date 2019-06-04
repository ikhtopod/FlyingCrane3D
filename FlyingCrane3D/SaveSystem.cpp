#include "SaveSystem.h"


SaveSystem::SaveSystem(std::string _server, std::string _login,
					   std::string _password, std::string _database) :
	DBConnect(_server, _login, _password, _database) {}


void SaveSystem::save(std::string sceneName, std::string categoryName) {
	if (this->isConnectionError()) return;

	Application* appThis = Application::getInstancePtr();

	// заполнить таблицу scenes
	int32_t sceneId = this->getColumnMax("scenes", "id") + 1;
	int32_t categoryId = this->getCategoryIdByName(categoryName);

	std::stringstream addSceneReq {};
	addSceneReq << "insert into scenes (id, name, category_id) values " <<
		"(" << sceneId << ", '" << sceneName << "', " << categoryId << ")";

	if (this->query(addSceneReq.str()) != 0) {
		std::cout << mysql_error(this->connection) << std::endl;
		return;
	}//fi

	for (auto&[objectName, objectShape] : appThis->getScene().getObjects()) {
		// заполнить таблицу objects
		int32_t objectId = this->getColumnMax("objects", "id") + 1;

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
			int32_t meshId = this->getColumnMax("meshes", "id") + 1;

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
