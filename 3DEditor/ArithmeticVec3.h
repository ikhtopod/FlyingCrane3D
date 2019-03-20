#pragma once

class ArithmeticVec3 {
private:
	glm::vec3 value;
public:
	ArithmeticVec3();
	ArithmeticVec3(glm::vec3 _value);
	virtual ~ArithmeticVec3() = default;

	virtual glm::vec3 getValue() const;
	virtual void setValue(const glm::vec3& _value);

	virtual void add(const glm::vec3& _value);
	virtual void sub(const glm::vec3& _value);
	virtual void mul(const glm::vec3& _value);
	virtual void div(const glm::vec3& _value);

	virtual void add(ArithmeticVec3& _value);
	virtual void sub(ArithmeticVec3& _value);
	virtual void mul(ArithmeticVec3& _value);
	virtual void div(ArithmeticVec3& _value);
};
