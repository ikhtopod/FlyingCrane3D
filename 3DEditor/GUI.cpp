#include "GUI.h"

const std::string GUI::FONT_DIRECTORY = "../resources/fonts";
const std::string GUI::FONT_PATH = FONT_DIRECTORY + "/Roboto-Regular.ttf";
const float GUI::DEFAULT_FONT_SIZE = 16.0f;


GUI::GUI() : fontSize(GUI::DEFAULT_FONT_SIZE) {}


float GUI::getFontSize() {
	return this->fontSize;
}

void GUI::setFontSize(float _fontSize) {
	this->fontSize = _fontSize;
}


void GUI::initFont() {
	ImGuiIO& io = ImGui::GetIO();

	static const ImWchar ranges[] = { 0x0020, 0xFFFF, 0 };

	ImFontConfig icons_config;
	icons_config.MergeMode = false;

	io.Fonts->AddFontFromFileTTF(FONT_PATH.c_str(), this->fontSize, &icons_config, ranges);

	io.Fonts->AddFontDefault();
}


void GUI::init() {
	this->bgColor = Application::getInstancePtr()->getBgColor();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// ImGuiIO& io = ImGui::GetIO(); //(void)io;
	ImGui::GetIO().IniFilename = nullptr;

	this->initFont();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(Application::getInstancePtr()->getWindow().getWindowPtr(), true);
	ImGui_ImplOpenGL3_Init();
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
}

void GUI::draw_Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void GUI::showMainMenuBar() {
	static bool showAboutWindow = false;

	if (ImGui::BeginMainMenuBar()) {
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
			if (ImGui::MenuItem("Настройки", "Ctrl + P")) {}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Справка")) {
			if (ImGui::MenuItem("О проекте", "F1", &showAboutWindow)) {}
			ImGui::EndMenu();
		}

		if (showAboutWindow) {
			ImGui::Begin("О проекте", &showAboutWindow);

			ImGui::Text("Дипломный проект на тему:\n\n");
			ImGui::Text("\"Разработка программной платформы интерактивной 3D-визуализации\"\n\n");
			ImGui::Separator();
			ImGui::Text("Виталий Лифанов. Группа ЗП3-2д");

			ImGui::End();
		}

		ImGui::EndMainMenuBar();
	}
}
