#pragma once

enum class TriadaMode {
	NONE,
	INIT,
	DRAW,
	FREE,
};

class ITriada {
public:
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void free() = 0;
};