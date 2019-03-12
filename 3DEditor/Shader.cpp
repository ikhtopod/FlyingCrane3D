#include "Shader.h"


const std::string Shader::DEFAULT_VERTEX_CODE =
R"(#version 330 core

layout (location = 0) in vec3 VertexPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Color;

void main(){
	Color = vec3(0.7f, 0.3f, 0.0f);
	gl_Position = (projection * view * model) * vec4(VertexPosition, 1.0f);
}
)";

const std::string Shader::DEFAULT_FRAGMENT_CODE =
R"(#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 Color;

void main() {
	FragColor = vec4(Color, 1.0f);
}
)";


Shader::Shader() : vertexCode(DEFAULT_VERTEX_CODE), fragmentCode(DEFAULT_FRAGMENT_CODE) {}

Shader::~Shader() {}


void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	GLuint lctn = glGetUniformLocation(this->id, name.c_str());
	glUniformMatrix4fv(lctn, 1, GL_FALSE, glm::value_ptr(value));
}


void Shader::init() {
	const GLchar* vShaderCode = this->vertexCode.c_str();
	const GLchar* fShaderCode = this->fragmentCode.c_str();

	constexpr unsigned int INFOLOG_SIZE = 512;

	GLint successChecker;
	GLchar infoLog[INFOLOG_SIZE];

	/* vertex */
	this->vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertex, 1, &vShaderCode, nullptr);
	glCompileShader(this->vertex);

	// print error vertex shader
	glGetShaderiv(this->vertex, GL_COMPILE_STATUS, &successChecker);

	if (!successChecker) {
		glGetShaderInfoLog(this->vertex, INFOLOG_SIZE, nullptr, infoLog);
		throw ShaderException(infoLog);
	}

	/* fragment */
	this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragment, 1, &fShaderCode, nullptr);
	glCompileShader(this->fragment);

	// print error fragment shader
	glGetShaderiv(this->fragment, GL_COMPILE_STATUS, &successChecker);

	if (!successChecker) {
		glGetShaderInfoLog(this->fragment, INFOLOG_SIZE, nullptr, infoLog);
		throw ShaderException(infoLog);
	}

	/* program */
	this->id = glCreateProgram();
	glAttachShader(this->id, this->vertex);
	glAttachShader(this->id, this->fragment);
	glLinkProgram(this->id);

	// print linking error program shader
	glGetProgramiv(this->id, GL_LINK_STATUS, &successChecker);

	if (!successChecker) {
		glGetProgramInfoLog(this->id, INFOLOG_SIZE, nullptr, infoLog);
		throw ShaderException(infoLog);
	}
}

void Shader::draw() {
	Application* appThis = Application::getInstancePtr();

	this->setMat4("model", appThis->getScene().getModel().getModel());
	this->setMat4("view", appThis->getScene().getModel().getView());
	this->setMat4("projection", appThis->getScene().getModel().getProjection());

	glUseProgram(this->id);
}

void Shader::free() {
	glDeleteShader(this->vertex);
	glDeleteShader(this->fragment);
	glDeleteProgram(this->id);
}


/* Exceptions */

ShaderException::ShaderException(char const* const message)
	: std::exception(message) {}
