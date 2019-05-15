#include "ObjectShape.h"


ObjectShape::ObjectShape() :
	Object(),
	pivotPoint(
		Mesh {
			PolymeshRepresentation {
				{
					Vertex{ glm::vec3 {}, 0 },
				},
				{ 0, 0, 0 }
			},
			GL_POINTS
		}
	) {}


void ObjectShape::init() {
	Object::init();

	this->pivotPoint.init();
}

void ObjectShape::draw() {
	Object::draw();

	if (this->canDrawPivotPoint) {
		this->pivotPoint.setParentTransform(this->parentTransform + this->transform);
		this->pivotPoint.draw();
	}//fi
}

void ObjectShape::free() {
	Object::free();

	this->pivotPoint.free();
}
