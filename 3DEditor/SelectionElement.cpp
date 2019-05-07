#include "SelectionElement.h"


void SelectionElement::drawObject(Object& object) {
	this->drawObject(object, CLEAR_COLOR);
}

// Отрисовать объект, чтобы вершины, спрятанные за ним, не выделялись
void SelectionElement::drawObject(Object& object, glm::vec4 color) {
	object.getSelectionInfo().colorSelect = color;
	object.getSelectionInfo().isSelectionProcess = true;

	for (auto&[meshKey, meshValue] : object.getMeshes()) {
		meshValue.setGlobalTransform(object.getParentTransform() + object.getTransform());
		meshValue.draw();
	}//rof

	object.getSelectionInfo().isSelectionProcess = false;
}
