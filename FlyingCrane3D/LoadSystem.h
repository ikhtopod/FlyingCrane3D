#pragma once

#include "DBConnect.h"

class LoadSystem : public DBConnect {
public:
	virtual ~LoadSystem() = default;

	void load();
};
