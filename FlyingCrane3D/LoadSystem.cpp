#include "LoadSystem.h"


LoadSystem::LoadSystem(std::string _server, std::string _login,
					   std::string _password, std::string _database) :
	DBConnect(_server, _login, _password, _database) {}

void LoadSystem::load(uint32_t sceneId) {

}
