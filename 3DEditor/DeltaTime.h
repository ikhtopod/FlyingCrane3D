#pragma once

class DeltaTime final {
private:
	float deltaTime;
	double lastTime;
public:
	DeltaTime();
	~DeltaTime();

	operator float();

	void update();
};
