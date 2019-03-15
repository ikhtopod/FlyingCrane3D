#pragma once

class ITriada {
public:
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void free() = 0;
};