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

/* ***** */

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

	while (!glfwWindowShouldClose(this->window.getWindowPtr())) {
		this->deltaTime.update();

		this->input();
		this->rendering();

		glfwPollEvents();
		glfwSwapBuffers(this->window.getWindowPtr());
	}
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
		this->scene.getCamera().keyboardMovement(CameraMovement::FORWARD, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_S) == GLFW_PRESS) {
		this->scene.getCamera().keyboardMovement(CameraMovement::BACKWARD, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_A) == GLFW_PRESS) {
		this->scene.getCamera().keyboardMovement(CameraMovement::LEFT, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_D) == GLFW_PRESS) {
		this->scene.getCamera().keyboardMovement(CameraMovement::RIGHT, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_E) == GLFW_PRESS) {
		this->scene.getCamera().keyboardMovement(CameraMovement::UP, deltaTime);
	}

	if (glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_Q) == GLFW_PRESS) {
		this->scene.getCamera().keyboardMovement(CameraMovement::DOWN, deltaTime);
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
	Application* appThis = Application::getInstancePtr();
	glfwSetWindowUserPointer(appThis->getWindow().getWindowPtr(), appThis);
	glfwSetFramebufferSizeCallback(appThis->getWindow().getWindowPtr(), Application::Callback::resizeWindow);
	glfwSetCursorPosCallback(appThis->getWindow().getWindowPtr(), Application::Callback::mouseMovementCallback);
}


void Application::Callback::resizeWindow(GLFWwindow* win, int width, int height) {
	Application* appThis = static_cast<Application*>(glfwGetWindowUserPointer(win));

	appThis->getWindow().getScreen().setWidthHeight(width, height);

	glViewport(0, 0, width, height);
}

void Application::Callback::mouseMovementCallback(GLFWwindow* win, double xPos, double yPos) {
	Application* appThis = static_cast<Application*>(glfwGetWindowUserPointer(win));

	static bool firstMouse = true;
	static float lastX = static_cast<float>(appThis->getInstance().getWindow().getScreen().getWidth());
	static float lastY = static_cast<float>(appThis->getInstance().getWindow().getScreen().getHeight());

	if (firstMouse) {
		lastX = static_cast<float>(xPos);
		lastY = static_cast<float>(yPos);
		firstMouse = false;
	}

	float xOffset = static_cast<float>(xPos) - lastX;
	float yOffset = lastY - static_cast<float>(yPos);
	lastX = static_cast<float>(xPos);
	lastY = static_cast<float>(yPos);

	appThis->getScene().getCamera().mouseMovement(xOffset, yOffset);
}


/* Exceptions */

ApplicationException::ApplicationException(char const* const message)
	: std::exception(message) {}


