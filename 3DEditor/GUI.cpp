#include "GUI.h"

const std::string GUI::FONT_DIRECTORY = "../resources/fonts";
const std::string GUI::FONT_PATH = FONT_DIRECTORY + "/Roboto-Regular.ttf";
const float GUI::DEFAULT_FONT_SIZE = 16.0f;


void GUI::initFont() {
	ImGuiIO& io = ImGui::GetIO();

	static const ImWchar ranges[] = { 0x0020, 0xFFFF, 0 };

	ImFontConfig icons_config;
	icons_config.MergeMode = false;

	io.Fonts->AddFontFromFileTTF(
		FONT_PATH.c_str(), this->fontSize, &icons_config, ranges);

	io.Fonts->AddFontDefault();
}

void GUI::updateToolsPanelByScreenSize() {
	ScreenResolution sr = Application::getInstancePtr()->getWindow().getScreen();
	this->updateToolsPanelByScreenSize(sr.getWidth(), sr.getHeight());
}

void GUI::updateToolsPanelByScreenSize(int width, int height) {
	this->updateToolsPanelByScreenSize(
		static_cast<float>(width), static_cast<float>(height));
}

void GUI::updateToolsPanelByScreenSize(float width, float height) {
	float wSize = 225.0f;
	this->sizeToolsPanel = ImVec2 { width > wSize ? wSize : width, height - this->positionToolsPanel.y };
	this->positionToolsPanel.x = width - this->sizeToolsPanel.x;
}

void GUI::init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::GetIO().IniFilename = nullptr;

	this->initFont();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(
		Application::getInstancePtr()->getWindow().getWindowPtr(), true);
	ImGui_ImplOpenGL3_Init();

	ImGui::InitDock();

	this->updateToolsPanelByScreenSize();
}

void GUI::draw() {
	this->draw_NewFrame();
	this->draw_GUI();
	this->draw_Render();
}

void GUI::free() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUI::draw_NewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUI::draw_GUI() {
	this->showMainMenuBar();
	this->showToolsPanel();
}

void GUI::draw_Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void GUI::showMainMenuBar() {
	static bool showAboutWindow = false;
	static bool showHotKeys = false;

	if (ImGui::BeginMainMenuBar()) {
		// Настроить панель Tools _под_ MenuBar
		if (this->positionToolsPanel.y != ImGui::GetWindowSize().y) {
			this->positionToolsPanel.y = ImGui::GetWindowSize().y;
			this->updateToolsPanelByScreenSize();
		}//fi

		if (ImGui::BeginMenu("Файл")) {
			if (ImGui::MenuItem("Новый", "Ctrl + N", false, false)) {}
			if (ImGui::MenuItem("Открыть", "Ctrl + O", false, false)) {}
			if (ImGui::MenuItem("Сохранить", "Ctrl + S", false, false)) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Импортировать", "", false, false)) {}
			if (ImGui::MenuItem("Экспортировать", "", false, false)) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Выход", "Ctrl + Q")) {
				Application::getInstancePtr()->quit();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Редактировать")) {
			if (ImGui::MenuItem("Настройки", "Ctrl + P", false, false)) {}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Справка")) {
			if (ImGui::MenuItem("Горячие клавиши", "", &showHotKeys)) {}

			if (ImGui::BeginMenu("Статистика")) {
				ImGui::Text(("FPS: " + std::to_string(ImGui::GetIO().Framerate)).c_str(), "");
				ImGui::Separator();
				ImGui::EndMenu();
			}

			ImGui::Separator();
			if (ImGui::MenuItem("О проекте", "F1", &showAboutWindow)) {}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();

		if (showAboutWindow) {
			ImGui::Begin("О проекте", &showAboutWindow);

			ImGui::Text("Дипломный проект на тему:"); ImGui::NewLine();
			ImGui::Text("\"Разработка программной платформы интерактивной 3D-визуализации\"");
			ImGui::NewLine();
			ImGui::Separator();
			ImGui::Text("Виталий Лифанов. Группа ЗП3-2д");

			ImGui::End();
		}

		if (showHotKeys) {
			ImGui::Begin("Горячие клавиши", &showHotKeys,
						 ImVec2(400, 400), -1.0f, ImGuiWindowFlags_NoResize);

			ImGui::Text("Tab: переключить камеру"); ImGui::NewLine();
			ImGui::Separator();
			ImGui::Text("Free Camera:"); ImGui::NewLine();
			ImGui::Text("W, A, S, D, Q, E: передвижение по сцене");
			ImGui::Text("Mouse: направление движения");
			ImGui::Text("Крутить СКМ: скорость"); ImGui::NewLine();
			ImGui::Separator();
			ImGui::Text("Target Camera:"); ImGui::NewLine();
			ImGui::Text("Зажать СКМ: вращение вокруг целевой точки");
			ImGui::Text("Shift + СКМ: смещение камеры и целевой точки в стороны");
			ImGui::Text("Крутить СКМ: изменение расстояния от целевой точки"); ImGui::NewLine();
			ImGui::Separator();
			ImGui::Text("Проекция:"); ImGui::NewLine();
			ImGui::Text("O: ортографическая");
			ImGui::Text("P: перспективная"); ImGui::NewLine();
			ImGui::Separator();
			ImGui::Text("Выделение:"); ImGui::NewLine();
			ImGui::Text("ЛКМ: выделить объект");
			ImGui::Text("Shift + ЛКМ: выделить несколько объектов");
			ImGui::Text("F: центрировать камеру на выделенных объектах");
			ImGui::Text("X: удалить выделенные объекты"); ImGui::NewLine();
			ImGui::Text("Сменить режим выделения:"); ImGui::NewLine();
			ImGui::Text("1: выделение вершин");
			ImGui::Text("2: выделение ребер");
			ImGui::Text("3: выделение граней");
			ImGui::Text("4: выделение объектов");
			ImGui::Separator();
			ImGui::Text("Действия с выделенными объектами:"); ImGui::NewLine();
			ImGui::Text("G: перемещение");
			ImGui::Text("R: вращение");
			ImGui::Text("S: масштабирование"); ImGui::NewLine();
			ImGui::Separator();

			ImGui::End();
		}

	}
}

void GUI::showToolsPanel() {
	if (ImGui::Begin("Tools", nullptr, this->sizeToolsPanel, -1.0f,
					 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
		ImGui::SetWindowSize(this->sizeToolsPanel, true);
		ImGui::SetWindowPos(this->positionToolsPanel, true);
		ImGui::BeginDockspace();

		if (ImGui::BeginDock("Dock 1")) {
			ImGui::Text("Header 1:"); ImGui::NewLine();
			ImGui::Text("Content 1");
			ImGui::Text("Content 2");
			ImGui::Text("Content 3"); ImGui::NewLine();
			ImGui::Separator();
		}
		ImGui::EndDock();

		if (ImGui::BeginDock("Dock 2")) {
			ImGui::Text("Header 1:"); ImGui::NewLine();
			ImGui::Text("Content 1");
			ImGui::Text("Content 2");
			ImGui::Text("Content 3"); ImGui::NewLine();
			ImGui::Separator();
		}
		ImGui::EndDock();

		ImGui::EndDockspace();
	}//fi Tools
	ImGui::End();
}
