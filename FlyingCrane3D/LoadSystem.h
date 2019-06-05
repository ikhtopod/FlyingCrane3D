#pragma once

#include "DBConnect.h"

class LoadSystem : public DBConnect {
public:
	LoadSystem() = delete;
	LoadSystem(std::string _server,
			   std::string _login,
			   std::string _password,
			   std::string _database);
	virtual ~LoadSystem() = default;

	void load(std::string sceneName);
};
