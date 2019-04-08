#pragma once

#include "Util.h"
#include "Application.h"
#include "Projection.h"

class Model final {
private:
	glm::mat4 model { Util::IDENTITY_MATRIX };
	glm::mat4 view { Util::IDENTITY_MATRIX };
	glm::mat4 projection { Util::IDENTITY_MATRIX };

	Projection orthoProj {};

public:
	Model() = default;
	~Model() = default;

	glm::mat4 getModel();
	glm::mat4 getView();
	glm::mat4 getProjection();

	glm::mat4 getModelViewProjection();

	void setModel(glm::mat4 _model);
	void setView(glm::mat4 _view);
	void setProjection(glm::mat4 _projection);

	Projection& getOrthoProj();

	void update();
};
