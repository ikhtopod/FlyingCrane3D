#pragma once

#include "DBConnect.h"

class SaveSystem : public DBConnect {
protected:
	uint32_t getFreeRow(std::string tableName, std::string colIdName);

public:
	SaveSystem() = delete;
	SaveSystem(std::string _server,
			   std::string _login,
			   std::string _password,
			   std::string _database);
	virtual ~SaveSystem() = default;

	void save(std::string sceneName, std::string categoryName);
};
