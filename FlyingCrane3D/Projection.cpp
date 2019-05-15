#include "Projection.h"


Projection::Projection() : projectionType(ProjectionType::PERSPECTIVE) {
	this->setScaleByDistance(TargetCamera::DEFAULT_DISTANCE);
}

ProjectionType Projection::getProjectionType() {
	return this->projectionType;
}

void Projection::setProjectionType(ProjectionType _projectionType) {
	if (this->projectionType != _projectionType) {
		this->projectionType = _projectionType;
	}
}

void Projection::switchToPerspective() {
	this->setProjectionType(ProjectionType::PERSPECTIVE);
}

void Projection::switchToOrthographic() {
	this->setProjectionType(ProjectionType::ORTHOGRAPHIC);
}

glm::vec3 Projection::getScale() {
	return this->scale;
}

void Projection::setScale(glm::vec3 _scale) {
	this->scale = _scale;
}

void Projection::setScaleByDistance(float distance) {
	this->scale = glm::vec3(1.0f) / distance;
}

glm::mat4 Projection::getMatrix() {
	Application* appThis = Application::getInstancePtr();

	float winWidth = static_cast<float>(appThis->getWindow().getScreen().getWidth());
	float winHeight = static_cast<float>(appThis->getWindow().getScreen().getHeight());

	glm::mat4 proj {};
	if (this->projectionType == ProjectionType::PERSPECTIVE) {
		float fov = appThis->getScene().getCamera().getFoV();
		proj = glm::perspective(glm::radians(fov), winWidth / winHeight, 0.1f, 100.0f);
	} else if (this->projectionType == ProjectionType::ORTHOGRAPHIC) {
		proj = glm::ortho(-winWidth / winHeight * 0.5f, winWidth / winHeight * 0.5f, -0.5f, 0.5f, -10.0f, 100.0f);
		proj = glm::scale(proj, this->scale);
	}

	return proj;
}

bool Projection::isPerspective() {
	return this->projectionType == ProjectionType::PERSPECTIVE;
}

bool Projection::isOrthographic() {
	return this->projectionType == ProjectionType::ORTHOGRAPHIC;
}

