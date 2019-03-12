#pragma once

class Axis final {
public:
	static const glm::vec3 X;
	static const glm::vec3 Y;
	static const glm::vec3 Z;

	static const glm::vec3 RIGHT;
	static const glm::vec3 PITCH;

	static const glm::vec3 UP;
	static const glm::vec3 YAW;

	static const glm::vec3 FRONT;
	static const glm::vec3 FORWARD;
	static const glm::vec3 ROLL;

	static const glm::vec3 LEFT;
	static const glm::vec3 DOWN;
	static const glm::vec3 BACK;
	static const glm::vec3 BACKWARD;

private:
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 front;

public:
	Axis();
	Axis(glm::vec3 _right, glm::vec3 _up, glm::vec3 _front);
	~Axis();

	glm::vec3 getRight();
	glm::vec3 getUp();
	glm::vec3 getFront();

	void setRight(glm::vec3 _right);
	void setUp(glm::vec3 _up);
	void setFront(glm::vec3 _front);
};
