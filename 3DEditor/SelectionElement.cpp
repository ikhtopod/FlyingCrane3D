#include "SelectionElement.h"

void SelectionElement::drawObject(Object& object) {
	this->drawObject(object, CLEAR_COLOR);
}

void SelectionElement::drawObject(Object& object, glm::vec4 color) {
	// Отрисовать объект, чтобы вершины, спрятанные за ним, не выделялись
	for (auto&[meshKey, meshValue] : object.getMeshes()) {
		this->shader.setLambdaDraw([&object, color](Shader* _this) {
			_this->setVec4("colorCode", color);
		});

		Shader prevShader = meshValue.getShader();
		meshValue.setShader(this->shader);
		meshValue.setGlobalTransform(object.getParentTransform() + object.getTransform());
		meshValue.draw();
		meshValue.setShader(prevShader);
	}//rof
}
