#pragma once

#include "DBConnect.h"

class SaveSystem : public DBConnect {
public:
	virtual ~SaveSystem() = default;

	void save(std::string sceneName);
};
