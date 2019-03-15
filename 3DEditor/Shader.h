#pragma once

#include "ITriada.h"
#include "Application.h"

class Shader : public ITriada {
private:
	static const std::string DEFAULT_VERTEX_SOURCE;
	static const std::string DEFAULT_FRAGMENT_SOURCE;

private:
	GLuint id;

	std::string vertexSource;
	std::string fragmentSource;

	GLuint vertex;
	GLuint fragment;

	glm::vec3 objectColor { .7f, .3f, .0f };
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

	glm::vec3 getObjectColor();
	void setObjectColor(glm::vec3 _color);

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;

	virtual void init() override;
	virtual void draw() override;
	virtual void free() override;

};


/* Exceptions */

class ShaderException : std::exception {
public:
	explicit ShaderException(char const* const message);
};
