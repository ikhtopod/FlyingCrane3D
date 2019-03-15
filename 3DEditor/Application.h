#pragma once

#include "Window.h"
#include "DeltaTime.h"
#include "Scene.h"
#include "ITriada.h"

class Application final : public ITriada {
private:
	static Application* instance;
	static void initInstance(Application*);

	Window window;
	DeltaTime deltaTime { 60 };
	Scene scene {};

	glm::vec4 bgColor { .2f, .2f, .3f, 1.0f };

public:
	Application();
	Application(std::string appTitle);
	Application(std::string appTitle, int sWidth, int sHeight);
	~Application() = default;

	static Application& getInstance();
	static Application* getInstancePtr();

	Window& getWindow();
	DeltaTime& getDeltaTime();
	Scene& getScene();
	glm::vec4 getBgColor();

	void run();

private:
	void loadGLLoader() const;

	void mainLoop();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

	void pressedEscape();
	void keyboardMovement();
	void input();

	void clearColor();
	void rendering();

private:
	class Callback final {
	public:
		Callback() = delete;
		~Callback();
		static void assignAll();
	private:
		static void resizeWindow(GLFWwindow* win, int width, int height);
		static void mouseMovementCallback(GLFWwindow* win, double xPos, double yPos);
	};
};


/* Exceptions */

class ApplicationException : std::exception {
public:
	explicit ApplicationException(char const* const message);
};

