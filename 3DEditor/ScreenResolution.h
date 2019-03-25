#pragma once

class ScreenResolution final {
private:
	int width;
	int height;

	double halfWidth;
	double halfHeight;

public:
	static const int DEFAULT_SCREEN_WIDTH;
	static const int DEFAULT_SCREEN_HEIGHT;

public:
	ScreenResolution();
	ScreenResolution(int sWidth, int sHeight);
	~ScreenResolution() = default;

	int getWidth();
	int getHeight();
	double getHalfWidth();
	double getHalfHeight();

	void setWidth(int _width);
	void setHeight(int _height);

	void setWidthHeight(int _width, int _height);
};

