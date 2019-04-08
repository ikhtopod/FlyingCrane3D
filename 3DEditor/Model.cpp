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

Projection& Model::getOrthoProj() {
	return this->orthoProj;
}


void Model::update() {
	Application* appThis = Application::getInstancePtr();

	this->setProjection(this->orthoProj.getMatrix());
	this->setView(appThis->getScene().getCamera().GetViewMatrix());
	this->setModel(Util::IDENTITY_MATRIX);
}
