#pragma once

#include "Util.h"
#include "ITriada.h"
#include "Application.h"
#include "ScreenResolution.h"

class GUI final : public ITriada {
public:
	static const std::string FONT_DIRECTORY;
	static const std::string FONT_PATH;
	static const float DEFAULT_FONT_SIZE;

private:
	float fontSize = DEFAULT_FONT_SIZE;

	ImVec2 sizeToolsPanel {};
	ImVec2 positionToolsPanel {};

	ImVec2 sizeToolBarPanel {};
	ImVec2 positionToolBarPanel {};

public:
	GUI() = default;
	~GUI() = default;

	void updatePanelsByScreenSize();
	void updatePanelsByScreenSize(int width, int height);
	void updatePanelsByScreenSize(float width, float height);
	void updatePanelsUnderMenuBar(float yPosition);

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

private:
	void draw_NewFrame();
	void draw_GUI();
	void draw_Render();

	void initFont();

private:
	void showMainMenuBar();
	void showToolBar();
	void showToolsPanel();
};
