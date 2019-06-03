#include "SaveSystem.h"


SaveSystem::SaveSystem(std::string _server, std::string _login,
					   std::string _password, std::string _database) :
	DBConnect(_server, _login, _password, _database) {}

void SaveSystem::save(std::string sceneName) {

}
