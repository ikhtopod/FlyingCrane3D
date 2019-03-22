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

glm::vec4 Application::getBgColor() {
	return this->bgColor;
}

void Application::run() {
	try {
		this->init();
		this->draw();
		this->free();
	} catch (std::exception e) {
		this->window.close();
		throw e;
	}
}



void Application::loadGLLoader() const {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw ApplicationException("Error in Application::loadGLLoader: gladLoadGLLoader is 0");
	}
}


void Application::mainLoop() {
	while (!glfwWindowShouldClose(this->window.getWindowPtr())) {
		this->input();
		this->rendering();

		glfwPollEvents();
		glfwSwapBuffers(this->window.getWindowPtr());

		this->deltaTime.update(this->window.isVSync());
	}
}


void Application::init() {
	try {
		this->window.init();
		this->loadGLLoader();
		Application::Callback::assignAll();

		glfwSetInputMode(this->window.getWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide cursor

		this->scene.init();
	} catch (std::exception e) {
		throw e;
	}
}

void Application::draw() {
	glEnable(GL_MULTISAMPLE);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	this->mainLoop();
}

void Application::free() {
	this->window.close();
	this->scene.free();
}

void Application::pressedEscape() {
	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(this->window.getWindowPtr(), GLFW_TRUE);
	}
}

void Application::keyboardMovement() {
	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_W) == GLFW_PRESS) {
		this->scene.getCamera().keyboardInput(CameraMovement::FORWARD, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_S) == GLFW_PRESS) {
		this->scene.getCamera().keyboardInput(CameraMovement::BACKWARD, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_A) == GLFW_PRESS) {
		this->scene.getCamera().keyboardInput(CameraMovement::LEFT, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_D) == GLFW_PRESS) {
		this->scene.getCamera().keyboardInput(CameraMovement::RIGHT, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_E) == GLFW_PRESS) {
		this->scene.getCamera().keyboardInput(CameraMovement::UP, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_Q) == GLFW_PRESS) {
		this->scene.getCamera().keyboardInput(CameraMovement::DOWN, deltaTime);
	}
}

void Application::input() {
	this->pressedEscape();
	this->keyboardMovement();
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

Application::Callback::~Callback() {}


void Application::Callback::assignAll() {
	Application* _this = Application::getInstancePtr();
	glfwSetWindowUserPointer(_this->getWindow().getWindowPtr(), _this);
	glfwSetFramebufferSizeCallback(_this->getWindow().getWindowPtr(), Application::Callback::resizeWindow);
	glfwSetCursorPosCallback(_this->getWindow().getWindowPtr(), Application::Callback::mouseMovementCallback);
}


void Application::Callback::resizeWindow(GLFWwindow* win, int width, int height) {
	Application* _this = static_cast<Application*>(glfwGetWindowUserPointer(win));

	_this->getWindow().getScreen().setWidthHeight(width, height);

	glViewport(0, 0, width, height);
}

void Application::Callback::mouseMovementCallback(GLFWwindow* win, double xPos, double yPos) {
	Application* _this = static_cast<Application*>(glfwGetWindowUserPointer(win));
	_this->getScene().getCamera().mouseInput(static_cast<float>(xPos), static_cast<float>(yPos));
}


/* Exceptions */

ApplicationException::ApplicationException(char const* const message)
	: std::exception(message) {}


