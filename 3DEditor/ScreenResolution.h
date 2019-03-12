#pragma once

class ScreenResolution final {
private:
	int width;
	int height;
public:
	static const int DEFAULT_SCREEN_WIDTH;
	static const int DEFAULT_SCREEN_HEIGHT;

public:
	ScreenResolution();
	ScreenResolution(int sWidth, int sHeight);
	~ScreenResolution();

	int getWidth();
	void setWidth(int _width);

	int getHeight();
	void setHeight(int _height);

	void setWidthHeight(int _width, int _height);
};

