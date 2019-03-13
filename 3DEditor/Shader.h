#pragma once

#include "Application.h"

class Shader {
private:
	static const std::string DEFAULT_VERTEX_SOURCE;
	static const std::string DEFAULT_FRAGMENT_SOURCE;

private:
	GLuint id;

	std::string vertexSource;
	std::string fragmentSource;

	GLuint vertex;
	GLuint fragment;

private:
	static constexpr unsigned int INFOLOG_SIZE = 512;

	GLint successChecker;
	GLchar infoLog[Shader::INFOLOG_SIZE];

	void vertexInit();
	void fragmentInit();
	void programInit();

public:
	Shader();
	Shader(std::string _vertexSource, std::string _fragmentSource);
	~Shader() = default;

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
