#pragma once

class DeltaTime final {
private:
	float deltaTime;
	double lastTime;
	float fps;
	float duration_fps;

public:
	static const int DEFAULT_FPS;

public:
	DeltaTime();
	DeltaTime(unsigned int _fps);
	~DeltaTime() = default;

	float getFPS();
	void setFPS(float _fps);

	float getDurationFPS();

	operator float();
	operator std::string();

	void update();
	void update(bool isVSync);
};
