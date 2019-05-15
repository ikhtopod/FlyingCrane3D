#include "Window.h"


void Window::initWindowHints() const {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 4); // multisampling MSAA
}


Window::Window(std::string sTitle)
	: Window(sTitle, ScreenResolution::DEFAULT_SCREEN_WIDTH,
			 ScreenResolution::DEFAULT_SCREEN_HEIGHT) {}


Window::Window(std::string sTitle, int sWidth, int sHeight)
	: screenTitle(sTitle), screen(sWidth, sHeight), vSync(GLFW_FALSE) {}


ScreenResolution& Window::getScreen() {
	return this->screen;
}

bool Window::isVSync() {
	return this->vSync;
}

void Window::setVSync(bool _vSync) {
	if (this->vSync != _vSync) {
		this->vSync = _vSync;
		glfwSwapInterval(this->vSync);
	}
}


GLFWwindow* Window::getWindowPtr() {
	return this->window;
}


void Window::init() {
	if (!glfwInit()) {
		throw WindowException("Error in Window::init(): !glfwInit()");
	}

	initWindowHints();

	this->window = glfwCreateWindow(this->screen.getWidth(),
									this->screen.getHeight(),
									this->screenTitle.c_str(),
									nullptr, nullptr);

	if (!this->window) {
		throw WindowException("Error in Window::init(): GLFWwindow is 0");
	}

	glfwMakeContextCurrent(this->window);
}

void Window::extra() {
	glfwMaximizeWindow(this->window);
	glfwSwapInterval(this->vSync);
}

void Window::close() {
	if (this->window) {
		glfwDestroyWindow(this->window);
	}

	glfwTerminate();
}


WindowException::WindowException(char const* const message)
	: std::exception(message) {}
