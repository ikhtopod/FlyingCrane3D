#include "GUI.h"

const std::string GUI::FONT_DIRECTORY = "../resources/fonts";
const std::string GUI::FONT_PATH = FONT_DIRECTORY + "/Roboto-Regular.ttf";
const float GUI::DEFAULT_FONT_SIZE = 16.0f;


void GUI::initIcons() {
	this->icons.insert({ GUIIcons::MOVING, Texture { R"(..\resources\icons\multimedia-icons\png\move.png)" } });
}

void GUI::initFont() {
	ImGuiIO& io = ImGui::GetIO();

	static const ImWchar ranges[] = { 0x0020, 0xFFFF, 0 };

	ImFontConfig icons_config;
	icons_config.MergeMode = false;

	io.Fonts->AddFontFromFileTTF(
		FONT_PATH.c_str(), this->fontSize, &icons_config, ranges);

	io.Fonts->AddFontDefault();
}

void GUI::updatePanelsByScreenSize() {
	ScreenResolution sr = Application::getInstancePtr()->getWindow().getScreen();
	this->updatePanelsByScreenSize(sr.getWidth(), sr.getHeight());
}

void GUI::updatePanelsByScreenSize(int width, int height) {
	this->updatePanelsByScreenSize(
		static_cast<float>(width), static_cast<float>(height));
}

void GUI::updatePanelsByScreenSize(float width, float height) {
	this->sizeToolBarPanel = ImVec2 { width, 50.0f };

	this->sizeToolsPanel = ImVec2 { 300.0f, height - this->sizeToolBarPanel.y };
	this->positionToolsPanel.y = this->sizeToolBarPanel.y + this->positionToolBarPanel.y;
	this->positionToolsPanel.x = width - this->sizeToolsPanel.x;
}

void GUI::updatePanelsUnderMenuBar(float yPosition) {
	if (this->positionToolBarPanel.y == yPosition) return;

	this->positionToolBarPanel.y = yPosition;
	this->updatePanelsByScreenSize();
}

void GUI::init() {
	this->initIcons();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;

	this->initFont();

	ImGui::StyleColorsLight();

	ImGui_ImplGlfw_InitForOpenGL(
		Application::getInstancePtr()->getWindow().getWindowPtr(), true);
	ImGui_ImplOpenGL3_Init();

	ImGui::InitDock();

	this->updatePanelsByScreenSize();
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
	this->showToolBar();
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
		this->updatePanelsUnderMenuBar(ImGui::GetWindowSize().y);

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
		}//fi BeginMenu

		if (ImGui::BeginMenu("Редактировать")) {
			if (ImGui::MenuItem("Настройки", "Ctrl + P", false, false)) {}

			ImGui::EndMenu();
		}//fi BeginMenu

		if (ImGui::BeginMenu("Справка")) {
			if (ImGui::MenuItem("Горячие клавиши", "", &showHotKeys)) {}
			ImGui::Separator();
			if (ImGui::MenuItem("О проекте", "F1", &showAboutWindow)) {}

			ImGui::EndMenu();
		}//fi BeginMenu

		ImGui::EndMainMenuBar();

		if (showAboutWindow) {
			if (ImGui::Begin("О проекте", &showAboutWindow)) {
				ImGui::Text("Дипломный проект на тему:"); ImGui::NewLine();
				ImGui::Text("\"Разработка программной платформы интерактивной 3D-визуализации\"");
				ImGui::NewLine();
				ImGui::Separator();
				ImGui::Text("Виталий Лифанов. Группа ЗП3-2д");
			}//fi Begin
			ImGui::End();
		}//fi showAboutWindow

		if (showHotKeys) {
			if (ImGui::Begin("Горячие клавиши", &showHotKeys,
							 ImVec2(400, 400), -1.0f, ImGuiWindowFlags_NoResize)) {

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
				ImGui::Text("4: выделение объектов"); ImGui::NewLine();
				ImGui::Separator();
				ImGui::Text("Действия с выделенными объектами:"); ImGui::NewLine();
				ImGui::Text("G: перемещение");
				ImGui::Text("R: вращение");
				ImGui::Text("S: масштабирование"); ImGui::NewLine();
				ImGui::Separator();
			}//fi Begin
			ImGui::End();
		}//fi showHotKeys

	}//fi BeginMainMenuBar
}

void GUI::showToolBar() {
	std::string nameToolBar { "ToolBar" };

	Application* appThis = Application::getInstancePtr();
	Scene& scene = appThis->getScene();

	if (ImGui::Begin(nameToolBar.c_str(), nullptr, this->sizeToolsPanel, -1.0f,
					 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
					 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar)) {

		ImGui::SetWindowSize(this->sizeToolBarPanel, true);
		ImGui::SetWindowPos(this->positionToolBarPanel, true);

		float sizeMoveButton = 29.0f;
		float spacing_w = this->sizeToolBarPanel.y / 2.0f;

		Texture& iconMoveButton = this->icons[GUIIcons::MOVING];
		ImGui::ImageButton((ImTextureID)iconMoveButton.getId(), ImVec2 { sizeMoveButton, sizeMoveButton });
		if (ImGui::IsItemClicked()) {
			std::cout << "w: " << iconMoveButton.getWidth() << ", h: " << iconMoveButton.getHeight() << std::endl;
		}

		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Перемещение\nвыделенных\nобъектов (G)");
		}//fi IsItemHovered Button

		ImGui::SameLine();

		if (ImGui::Button("R", ImVec2 { sizeMoveButton, sizeMoveButton })) {
		}//fi Button
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Вращение\nвыделенных\nобъектов (R)");
		}//fi IsItemHovered Button

		ImGui::SameLine();

		if (ImGui::Button("S", ImVec2 { sizeMoveButton, sizeMoveButton })) {
		}//fi Button
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Масштабирование\nвыделенных\nобъектов (S)");
		}//fi IsItemHovered Button

		ImGui::SameLine(0.0f, spacing_w);

		if (ImGui::Button("O", ImVec2 { sizeMoveButton, sizeMoveButton })) {
			if (scene.getCameraSwitcher().getType() == CameraType::TARGET) {
				scene.getModel().getOrthoProj().switchToOrthographic();
			}
		}//fi Button
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Ортографический\nвид (O)");
		}//fi IsItemHovered Button

		ImGui::SameLine();

		if (ImGui::Button("P", ImVec2 { sizeMoveButton, sizeMoveButton })) {
			scene.getModel().getOrthoProj().switchToPerspective();
		}//fi Button
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Перспективный\nвид (P)");
		}//fi IsItemHovered Button

		ImGui::SameLine(0.0f, spacing_w);

		if (ImGui::Button("C", ImVec2 { sizeMoveButton, sizeMoveButton })) {
			if ((scene.getCameraSwitcher().getType() == CameraType::TARGET &&
				 scene.getSelectionSwitcher().getActionMode() == SelectionActionMode::NONE) ||
				scene.getCameraSwitcher().getType() == CameraType::FREE) {

				scene.getCameraSwitcher().switchCamera();
			}//fi
		}//fi Button
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Переключить\nтип камеры (Tab)");
		}//fi IsItemHovered Button

		ImGui::SameLine(0.0f, spacing_w);
	}//fi Begin
	ImGui::End();
}

void GUI::showToolsPanel() {
	std::string nameMainTools { "Панель инструментов" };

	if (ImGui::Begin(nameMainTools.c_str(), nullptr, this->sizeToolsPanel, -1.0f,
					 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
		ImGui::SetWindowSize(this->sizeToolsPanel, true);
		ImGui::SetWindowPos(this->positionToolsPanel, true);

		ImGui::BeginDockspace();

		ImGui::SetNextDock(nameMainTools.c_str(), ImGuiDockSlot_Tab);
		if (ImGui::BeginDock("Свойства")) {
			ImGui::TextColored(ImVec4 { 0.6f, 0.7f, 0.9f, 1.0f }, "Свойства:");
			ImGui::Separator();

			if (ImGui::CollapsingHeader("ImGui FPS", nullptr, ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::Text((std::to_string(ImGui::GetIO().Framerate)).c_str(), "");
			}//CollapsingHeader Transform

			ImGui::Separator();
		}//fi BeginDock
		ImGui::EndDock();

		ImGui::SetNextDock(nameMainTools.c_str(), ImGuiDockSlot_Tab);
		if (ImGui::BeginDock("Добавить объект")) {
			std::vector<const char *> listboxItems {
				"Плоскость", "Сетка",
				"Куб",
				"Конус", "Пирамида",
				"Цилиндр",
				"Сфера",
				"Пустышка"
			};
			static int currentListboxItem = 0;

			ImGui::ListBox("Список\nобъектов", &currentListboxItem, &(listboxItems)[0],
						   listboxItems.size(), listboxItems.size());

			ImGui::NewLine();
			ImGui::Button("Добавить");
			ImGui::Separator();
		}//fi BeginDock
		ImGui::EndDock();

		ImGui::EndDockspace();
	}//fi Begin
	ImGui::End();
}
