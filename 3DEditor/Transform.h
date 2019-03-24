#pragma once

#include "Util.h"

class Transform final {
public:
	static const glm::vec3 DEFAULT_POSITION;
	static const glm::vec3 DEFAULT_ROTATION;
	static const glm::vec3 DEFAULT_SCALE;

public:
	static Transform matrixToTransform(const glm::mat4& _matrix);

private:
	glm::vec3 position {};
	glm::vec3 rotation {};
	glm::vec3 scale {};

public:
	Transform();
	Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
	Transform(glm::mat4 matrix);
	Transform(const Transform& transform);
	~Transform() = default;

	Transform& operator=(const Transform& t1);

	Transform& operator+=(const Transform& t1);
	friend Transform operator+(Transform t1, const Transform& t2);

	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScale() const;

	glm::mat4 getPositionMat4() const;
	glm::mat4 getRotationMat4() const;
	glm::mat4 getScaleMat4() const;

	void setPosition(const glm::vec3& _position);
	void setRotation(const glm::vec3& _rotation);
	void setScale(const glm::vec3& _scale);

	glm::mat4 getMatrix() const;
};
