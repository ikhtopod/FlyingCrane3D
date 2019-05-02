#include "Application.h"


Application* Application::instance = nullptr;

void Application::initInstance(Application* _this) {
	if (Application::instance == nullptr) {
		Application::instance = _this;
	}
}


Application::Application() : Application("") {}

Application::Application(std::string appTitle)
	: Application(appTitle, ScreenResolution::DEFAULT_SCREEN_WIDTH,
				  ScreenResolution::DEFAULT_SCREEN_HEIGHT) {}

Application::Application(std::string appTitle, int sWidth, int sHeight)
	: window(appTitle, sWidth, sHeight), deltaTime(120) {

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

		//this->deltaTime.update();
		this->deltaTime.update(this->window.isVSync());
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
	glEnable(GL_PROGRAM_POINT_SIZE);
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
		if ((this->scene.getCameraSwitcher().getType() == CameraType::TARGET &&
			 this->scene.getSelectionSwitcher().getActionMode() == SelectionActionMode::NONE) ||
			this->scene.getCameraSwitcher().getType() == CameraType::FREE) {

			this->scene.getCameraSwitcher().switchCamera();
		}
		prevState = GLFW_PRESS;
	} else if (state == GLFW_RELEASE && prevState == GLFW_PRESS) {
		prevState = GLFW_RELEASE;
	}
}

void Application::switchProjectionInput() {
	static bool prevStateP = GLFW_RELEASE;
	static bool prevStateO = GLFW_RELEASE;

	int stateP = glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_P);

	if (stateP == GLFW_PRESS && prevStateP == GLFW_RELEASE) {
		this->scene.getModel().getOrthoProj().setProjectionType(ProjectionType::PERSPECTIVE);
		prevStateP = GLFW_PRESS;
		return;
	} else if (stateP == GLFW_RELEASE && prevStateP == GLFW_PRESS) {
		prevStateP = GLFW_RELEASE;
	}

	int stateO = glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_O);

	if (stateO == GLFW_PRESS && prevStateO == GLFW_RELEASE) {
		if (this->scene.getCameraSwitcher().getType() == CameraType::TARGET) {
			this->scene.getModel().getOrthoProj().setProjectionType(ProjectionType::ORTHOGRAPHIC);
		}
		prevStateO = GLFW_PRESS;
		return;
	} else if (stateO == GLFW_RELEASE && prevStateO == GLFW_PRESS) {
		prevStateO = GLFW_RELEASE;
	}
}

void Application::focusingOnSelectedObjects() {
	static bool prevState = GLFW_RELEASE;

	int state = glfwGetKey(this->window.getWindowPtr(), GLFW_KEY_F);

	if (state == GLFW_PRESS && prevState == GLFW_RELEASE) {
		if (this->scene.getCameraSwitcher().getType() == CameraType::TARGET &&
			this->scene.getSelectionSwitcher().getActionMode() == SelectionActionMode::NONE) {

			if (!this->scene.getSelection().getSelectedObjects().empty()) {
				std::shared_ptr<TargetCamera> tc =
					std::dynamic_pointer_cast<TargetCamera>(this->scene.getCameraSwitcher().getCamera());
				tc->setTargetPosition(this->scene.getSelection().getCentroid());
			}//fi

		}//fi
		prevState = GLFW_PRESS;
	} else if (state == GLFW_RELEASE && prevState == GLFW_PRESS) {
		prevState = GLFW_RELEASE;
	}//fi
}

void Application::input() {
	this->keyboardInput();
	this->switchCameraInput();
	this->scene.getSelectionSwitcher().switchSelectionInput();
	if (this->scene.getCameraSwitcher().getType() == CameraType::TARGET) {
		this->scene.getSelectionSwitcher().switchActionInput();
	}
	this->switchProjectionInput();
	this->focusingOnSelectedObjects();
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

	glfwSetFramebufferSizeCallback(_this->getWindow().getWindowPtr(), AppCall::resizeWindow);
	glfwSetCursorPosCallback(_this->getWindow().getWindowPtr(), AppCall::mouseMovementCallback);
	glfwSetMouseButtonCallback(_this->getWindow().getWindowPtr(), AppCall::mouseButtonCallback);
	glfwSetScrollCallback(_this->getWindow().getWindowPtr(), AppCall::scrollCallback);
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

	if (appThis->scene.getCameraSwitcher().getType() == CameraType::TARGET &&
		appThis->scene.getSelectionSwitcher().getActionMode() != SelectionActionMode::NONE) {

		appThis->scene.getSelectionSwitcher().mouseActionInput(button, action, mods);
	} else {
		appThis->getScene().getSelection().mouseButtonInput(button, action, mods);
	}
}

void Application::Callback::scrollCallback(GLFWwindow* win, double xOffset, double yOffset) {
	Application* appThis = static_cast<Application*>(glfwGetWindowUserPointer(win));

	if (appThis->getCurrentMode() != TriadaMode::DRAW) return;
	if (ImGui::IsMouseHoveringAnyWindow()) return;

	float xOffset_f = static_cast<float>(xOffset);
	float yOffset_f = static_cast<float>(yOffset);

	appThis->getScene().getCamera().mouseScrollInput(xOffset_f, yOffset_f);
}


/* Exceptions */

ApplicationException::ApplicationException(char const* const message)
	: std::exception(message) {}
