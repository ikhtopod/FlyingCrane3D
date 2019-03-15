#include "Model.h"


glm::mat4 Model::getModel() {
	return this->model;
}

glm::mat4 Model::getView() {
	return this->view;
}

glm::mat4 Model::getProjection() {
	return this->projection;
}

glm::mat4 Model::getModelViewProjection() {
	return this->projection * this->view * this->model;
}


void Model::setModel(glm::mat4 _model) {
	this->model = _model;
}

void Model::setView(glm::mat4 _view) {
	this->view = _view;
}

void Model::setProjection(glm::mat4 _projection) {
	this->projection = _projection;
}


void Model::update() {
	Application* appThis = Application::getInstancePtr();

	float winWidth = static_cast<float>(appThis->getWindow().getScreen().getWidth());
	float winHeight = static_cast<float>(appThis->getWindow().getScreen().getHeight());

	float fov = appThis->getScene().getCamera().getFoV();

	glm::mat4 persp = glm::perspective(glm::radians(fov), winWidth / winHeight, 0.1f, 100.0f);

	this->setProjection(persp);
	this->setView(appThis->getScene().getCamera().GetViewMatrix());
	this->setModel(Util::IDENTITY_MATRIX);
}
