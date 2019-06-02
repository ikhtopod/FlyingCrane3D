#pragma once

#include "DBConnect.h"

class SaveSystem : public DBConnect {
public:
	SaveSystem();
	virtual ~SaveSystem();

	void save(std::string sceneName);
};
