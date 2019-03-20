#pragma once

#include "Util.h"

class Transform final {
private:
	glm::vec3 position {};
	glm::vec3 rotation {};
	glm::vec3 scale {};

public:
	Transform();
	Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
	Transform(const Transform& transform);
	~Transform() = default;

	Transform& operator+=(const Transform& t1);
	friend Transform operator+(Transform t1, const Transform& t2);

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();

	void setPosition(glm::vec3 _position);
	void setRotation(glm::vec3 _rotation);
	void setScale(glm::vec3 _scale);

	glm::mat4 getMatrix();
};
