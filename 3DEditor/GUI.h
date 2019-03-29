#pragma once

#include "Util.h"
#include "ITriada.h"
#include "Application.h"

class GUI : public ITriada {
public:
	static const std::string FONT_DIRECTORY;
	static const std::string FONT_PATH;
	static const float DEFAULT_FONT_SIZE;

private:
	glm::vec4 bgColor { .2f, .2f, .3f, 1.0f };
	float fontSize;

public:
	GUI();
	~GUI() = default;

	float getFontSize();
	void setFontSize(float _fontSize);

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
};
