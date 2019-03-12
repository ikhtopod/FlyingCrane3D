#include "Window.h"


void Window::initWindowHints() const {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


Window::Window(std::string sTitle)
	: Window(sTitle, ScreenResolution::DEFAULT_SCREEN_WIDTH, ScreenResolution::DEFAULT_SCREEN_HEIGHT) {}


Window::Window(std::string sTitle, int sWidth, int sHeight)
	: screenTitle(sTitle), screen(sWidth, sHeight),
	vSync(GLFW_TRUE), isHideMouse(false) {}


Window::~Window() {}


ScreenResolution& Window::getScreen() {
	return this->screen;
}


GLFWwindow& Window::getWindow() {
	return *(this->window);
}

GLFWwindow* Window::getWindowPtr() {
	return this->window;
}


void Window::init() {
	if (!glfwInit()) {
		throw WindowException("Error in Window::init(): !glfwInit()");
	}

	initWindowHints();

	this->window = glfwCreateWindow(this->screen.getWidth(), this->screen.getHeight(), this->screenTitle.c_str(), nullptr, nullptr);
	if (!window) {
		throw WindowException("Error in Window::init(): GLFWwindow is 0");
	}

	glfwMakeContextCurrent(window);

	// On/off v-sync. Если v-sync включен, то fps ограничевается до 60 кадров
	glfwSwapInterval(this->vSync);

	// Спрятать мышь
	if (isHideMouse) {
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Window::close() {
	if (this->window) {
		glfwDestroyWindow(window);
	}

	glfwTerminate();
}


WindowException::WindowException(char const* const message)
	: std::exception(message) {}
