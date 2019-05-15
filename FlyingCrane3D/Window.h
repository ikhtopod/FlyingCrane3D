#pragma once

#include "ScreenResolution.h"

class Window final {
private:
	ScreenResolution screen;

	GLFWwindow* window;
	std::string screenTitle;
	bool vSync;

private:
	void initWindowHints() const;

public:
	Window() = delete;
	Window(std::string sTitle);
	Window(std::string sTitle, int sWidth, int sHeight);
	~Window() = default;

	ScreenResolution& getScreen();
	bool isVSync();

	void setVSync(bool _vSync);

	GLFWwindow* getWindowPtr();

	void init();
	void extra();

	void close();
};


class WindowException : std::exception {
public:
	explicit WindowException(char const* const message);
};
