#pragma once

#include "Application.h"

class Shader {
private:
	static const std::string DEFAULT_VERTEX_CODE;
	static const std::string DEFAULT_FRAGMENT_CODE;

private:
	GLuint id;

	std::string vertexCode;
	std::string fragmentCode;

	GLuint vertex;
	GLuint fragment;
public:
	Shader();
	~Shader();

	void setMat4(const std::string& name, glm::mat4 value) const;

	void init();
	void draw();
	void free();
};


/* Exceptions */

class ShaderException : std::exception {
public:
	explicit ShaderException(char const* const message);
};
