#pragma once

#include "Util.h"
#include "Window.h"
#include "GUI.h"
#include "DeltaTime.h"
#include "Scene.h"
#include "Projection.h"
#include "ITriada.h"
#include "Selection.h"


class Application final : public ITriada {
private:
	static Application* instance;
	static void initInstance(Application*);

	Window window;
	GUI gui;
	DeltaTime deltaTime;
	Scene scene {};

	TriadaMode currentMode = TriadaMode::NONE;

	glm::vec4 bgColor { .2f, .2f, .3f, 1.0f };

public:
	Application();
	Application(std::string appTitle);
	Application(std::string appTitle, int sWidth, int sHeight);
	~Application() = default;

	static Application& getInstance();
	static Application* getInstancePtr();

	Window& getWindow();
	GUI& getGui();
	DeltaTime& getDeltaTime();
	Scene& getScene();
	TriadaMode getCurrentMode();
	glm::vec4 getBgColor();

	void run();

public:
	void quit();

private:
	void loadGLLoader() const;

	void mainLoop();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

	void keyboardInput();
	void switchCameraInput();
	void switchProjectionInput();
	void focusingOnSelectedObjects();
	void input();

	void rendering();

private:
	class Callback final {
	private:
		using AppCall = Application::Callback;

	public:
		Callback() = delete;
		~Callback() = delete;
		static void assignAll();
	private:
		static void resizeWindow(GLFWwindow* win, int width, int height);
		static void mouseMovementCallback(GLFWwindow* win, double xPos, double yPos);
		static void mouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
		static void scrollCallback(GLFWwindow* win, double xOffset, double yOffset);
	};
};


/* Exceptions */

class ApplicationException : std::exception {
public:
	explicit ApplicationException(char const* const message);
};

