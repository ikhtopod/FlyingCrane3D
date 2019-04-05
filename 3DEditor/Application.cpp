#include "Application.h"


Application* Application::instance = nullptr;

void Application::initInstance(Application* _this) {
	if (Application::instance == nullptr) {
		Application::instance = _this;
	}
}


Application::Application() : Application("") {}

Application::Application(std::string appTitle) : window(appTitle) {
	Application::initInstance(this);
}

Application::Application(std::string appTitle, int sWidth, int sHeight)
	: window(appTitle, sWidth, sHeight) {

	Application::initInstance(this);
}


Application& Application::getInstance() {
	return *Application::instance;
}

Application* Application::getInstancePtr() {
	return Application::instance;
}


Window& Application::getWindow() {
	return this->window;
}

DeltaTime& Application::getDeltaTime() {
	return this->deltaTime;
}

Scene& Application::getScene() {
	return this->scene;
}

TriadaMode Application::getCurrentMode() {
	return this->currentMode;
}

glm::vec4 Application::getBgColor() {
	return this->bgColor;
}

void Application::run() {
	try {
		this->init();
		this->draw();
		this->free();
	} catch (std::exception e) {
		this->currentMode = TriadaMode::NONE;
		this->window.close();
		throw e;
	}

	this->currentMode = TriadaMode::NONE;
}

void Application::quit() {
	glfwSetWindowShouldClose(this->window.getWindowPtr(), GLFW_TRUE);
}


void Application::loadGLLoader() const {
	gladLoadGL();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw ApplicationException("Error in Application::loadGLLoader: gladLoadGLLoader is 0");
	}
}


void Application::mainLoop() {
	// WARNING: Последовательность вызовов функций важна!!!
	while (!glfwWindowShouldClose(this->window.getWindowPtr())) {
		glfwPollEvents();

		this->input();
		this->rendering();
		this->gui.draw();

		glfwSwapBuffers(this->window.getWindowPtr());

		this->deltaTime.update();
		//this->deltaTime.update(this->window.isVSync());
	}
}


void Application::init() {
	this->currentMode = TriadaMode::INIT;

	try {
		this->window.init();
		this->loadGLLoader();
		Application::Callback::assignAll();
		this->gui.init();
		this->scene.init();
	} catch (std::exception e) {
		this->currentMode = TriadaMode::NONE;
		throw e;
	}

	this->currentMode = TriadaMode::NONE;
}

void Application::draw() {
	this->currentMode = TriadaMode::DRAW;

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	this->mainLoop();

	this->currentMode = TriadaMode::NONE;
}

void Application::free() {
	this->currentMode = TriadaMode::FREE;

	this->window.close();
	this->gui.free();
	this->scene.free();

	this->currentMode = TriadaMode::NONE;
}

void Application::keyboardInput() {
	this->scene.getCamera().keyboardInput();
}

void Application::switchCameraInput() {
	static bool prevState = GLFW_RELEASE;

	int state = glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_TAB);

	if (state == GLFW_PRESS && prevState == GLFW_RELEASE) {
		this->scene.getCameraSwitcher().switchCamera();
		prevState = GLFW_PRESS;
	} else if (state == GLFW_RELEASE && prevState == GLFW_PRESS) {
		prevState = GLFW_RELEASE;
	}
}

void Application::input() {
	this->keyboardInput();
	this->switchCameraInput();
	this->scene.getSelectionSwitcher().switchSelectionInput();
}

void Application::clearColor() {
	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::rendering() {
	this->clearColor();
	this->scene.draw();
}


/* Callback */

void Application::Callback::assignAll() {
	Application* _this = Application::getInstancePtr();
	glfwSetWindowUserPointer(_this->getWindow().getWindowPtr(), _this);

	glfwSetFramebufferSizeCallback(_this->getWindow().getWindowPtr(), Application::Callback::resizeWindow);
	glfwSetCursorPosCallback(_this->getWindow().getWindowPtr(), Application::Callback::mouseMovementCallback);
	glfwSetMouseButtonCallback(_this->getWindow().getWindowPtr(), Application::Callback::mouseButtonCallback);
	glfwSetScrollCallback(_this->getWindow().getWindowPtr(), Application::Callback::scrollCallback);
}


void Application::Callback::resizeWindow(GLFWwindow* win, int width, int height) {
	Application* appThis = static_cast<Application*>(glfwGetWindowUserPointer(win));

	if (appThis->getCurrentMode() != TriadaMode::DRAW) return;

	appThis->getWindow().getScreen().setWidthHeight(width, height);

	glViewport(0, 0, width, height);
}

void Application::Callback::mouseMovementCallback(GLFWwindow* win, double xPos, double yPos) {
	Application* appThis = static_cast<Application*>(glfwGetWindowUserPointer(win));

	if (appThis->getCurrentMode() != TriadaMode::DRAW) return;

	float xPos_f = static_cast<float>(xPos);
	float yPos_f = static_cast<float>(yPos);
	appThis->getScene().getCamera().mouseInput(xPos_f, yPos_f);
}

void Application::Callback::mouseButtonCallback(GLFWwindow* win, int button, int action, int mods) {
	Application* appThis = static_cast<Application*>(glfwGetWindowUserPointer(win));

	if (appThis->getCurrentMode() != TriadaMode::DRAW) return;

	appThis->getScene().getCamera().mouseButtonInput(button, action, mods);
	appThis->getScene().getSelection().mouseButtonInput(button, action, mods);
}

void Application::Callback::scrollCallback(GLFWwindow* win, double xOffset, double yOffset) {
	Application* appThis = static_cast<Application*>(glfwGetWindowUserPointer(win));

	if (appThis->getCurrentMode() != TriadaMode::DRAW) return;

	appThis->getScene().getCamera().mouseScrollInput(static_cast<float>(xOffset), static_cast<float>(yOffset));
}


/* Exceptions */

ApplicationException::ApplicationException(char const* const message)
	: std::exception(message) {}


