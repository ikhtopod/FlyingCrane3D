#pragma once

#include "Util.h"
#include "ITriada.h"
#include "Application.h"
#include "ScreenResolution.h"
#include "Texture.h"

enum class GUIIcons : UINT8 {
	POINT, EDGE, FACE, OBJECT,
	MOVE, ROTATE, SCALE,
	REMOVE,
	PERSP, ORTHO,
	CAMERA, FOCUS
};

class GUI final : public ITriada {
private:
	using FSPath = std::filesystem::path;

public:
	static const std::string FONT_DIRECTORY;
	static const std::string FONT_PATH;
	static const float DEFAULT_FONT_SIZE;

	static const FSPath SAVE_DIRECTORY;
	static const FSPath SAVE_FILENAME;
	static const FSPath SAVE_PATH;

private:
	float fontSize = DEFAULT_FONT_SIZE;

	char serverName[255] = "";
	char login[255] = "";
	char password[255] = "";
	char dbName[255] = "";

	ImVec2 sizeToolsPanel {};
	ImVec2 positionToolsPanel {};

	ImVec2 sizeToolBarPanel {};
	ImVec2 positionToolBarPanel {};

	ImVec2 sizeObjectsListPanel {};
	ImVec2 positionObjectsListPanel {};

	std::unordered_map<GUIIcons, Texture> icons {};

public:
	GUI() = default;
	~GUI() = default;

	void updatePanelsByScreenSize();
	void updatePanelsByScreenSize(int width, int height);
	void updatePanelsByScreenSize(float width, float height);
	void updatePanelsUnderMenuBar(float yPosition);

	void updateSelectedObjectsTree();
	void updateSceneObjectsTree();

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

private:
	void draw_NewFrame();
	void draw_GUI();
	void draw_Render();

	void initIcons();
	void initFont();
	void updateServerSettings();

private:
	void showSavePanel(bool* showSave);
	void showLoadPanel(bool* showLoad);
	void showSettingsPanel(bool* showSettings);
	void showHotKeysPanel(bool* showHotKeys);
	void showAboutWindowPanel(bool* showAboutWindow);

private:
	void showMainMenuBar();
	void showToolBar();
	void showToolsPanel();
	void showObjectsListPanel();
};
