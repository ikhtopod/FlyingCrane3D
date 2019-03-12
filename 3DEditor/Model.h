#pragma once

#include "Application.h"

class Model final {
private:
	glm::mat4 model { IDENTITY_MATRIX };
	glm::mat4 view { IDENTITY_MATRIX };
	glm::mat4 projection { IDENTITY_MATRIX };
public:
	Model();
	~Model();

	glm::mat4 getModel();
	glm::mat4 getView();
	glm::mat4 getProjection();

	void setModel(glm::mat4 _model);
	void setView(glm::mat4 _view);
	void setProjection(glm::mat4 _projection);

	void update();
};