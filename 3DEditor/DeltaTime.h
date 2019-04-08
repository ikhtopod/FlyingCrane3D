#pragma once

using std::chrono::duration_cast;

class DeltaTime final {
private:
	using Mcrsec = std::chrono::microseconds;
	using Mlsec = std::chrono::milliseconds;
	using FpsClock = std::chrono::steady_clock;
	using timePointFps = std::chrono::time_point<FpsClock>;

private:
	Mcrsec deltaTime {};
	timePointFps lastTime;
	unsigned int fps;
	Mcrsec durationFps;

private:
	static float mcrsecToFloatCast(Mcrsec value);
	void updateDurationFps();

public:
	static const unsigned int DEFAULT_FPS;

public:
	DeltaTime();
	DeltaTime(unsigned int _fps);
	~DeltaTime() = default;

	unsigned int getFps();
	void setFps(unsigned int _fps);

	float getDurationFps();

	operator float();
	operator std::string();
	operator Mcrsec();

	void update();
	void update(bool isVSync);
};
