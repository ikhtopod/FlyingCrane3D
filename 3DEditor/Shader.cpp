#include "Shader.h"


/*************************/
/* Start default shaders */

const std::string Shader::DEFAULT_VERTEX_SOURCE =
R"glsl(#version 330 core

layout (location = 0) in vec3 VertexPosition;

uniform mat4 mvp; // model-view-projection

void main(){
	gl_Position = mvp * vec4(VertexPosition, 1.0f);
}
)glsl";

const std::string Shader::DEFAULT_FRAGMENT_SOURCE =
R"glsl(#version 330 core

layout (location = 0) out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
	FragColor = vec4(objectColor * lightColor, 1.0f);
}
)glsl";

/* End default shaders */
/***********************/


Shader::Shader() : vertexSource(DEFAULT_VERTEX_SOURCE), fragmentSource(DEFAULT_FRAGMENT_SOURCE) {}

Shader::Shader(std::string _vertexSource, std::string _fragmentSource)
	: vertexSource(_vertexSource), fragmentSource(_fragmentSource) {}

glm::vec3 Shader::getObjectColor() {
	return this->objectColor;
}

void Shader::setObjectColor(glm::vec3 _color) {
	this->objectColor = _color;
}


void Shader::setBool(const std::string& name, bool value) const {
	this->setInt(name, static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), static_cast<GLint>(value));
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(this->id, name.c_str()), static_cast<GLfloat>(value));
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	GLuint lctn = glGetUniformLocation(this->id, name.c_str());
	glUniformMatrix4fv(lctn, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const {
	GLuint lctn = glGetUniformLocation(this->id, name.c_str());
	glUniform3fv(lctn, 1, &value[0]);
}


void Shader::vertexInit() {
	const GLchar* vShaderSource = this->vertexSource.c_str();

	this->vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertex, 1, &vShaderSource, nullptr);
	glCompileShader(this->vertex);

	// print error vertex shader
	glGetShaderiv(this->vertex, GL_COMPILE_STATUS, &successChecker);

	if (!successChecker) {
		glGetShaderInfoLog(this->vertex, INFOLOG_SIZE, nullptr, infoLog);
		throw ShaderException(infoLog);
	}
}

void Shader::fragmentInit() {
	const GLchar* fShaderCode = this->fragmentSource.c_str();

	this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragment, 1, &fShaderCode, nullptr);
	glCompileShader(this->fragment);

	// print error fragment shader
	glGetShaderiv(this->fragment, GL_COMPILE_STATUS, &successChecker);

	if (!successChecker) {
		glGetShaderInfoLog(this->fragment, INFOLOG_SIZE, nullptr, infoLog);
		throw ShaderException(infoLog);
	}
}

void Shader::programInit() {
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


void Shader::init() {
	try {
		this->vertexInit();
		this->fragmentInit();
		this->programInit();
	} catch (...) {
		throw;
	}
}

void Shader::draw() {
	Application* appThis = Application::getInstancePtr();

	this->setMat4("mvp", appThis->getScene().getModel().getModelViewProjection());

	this->setVec3("objectColor", this->objectColor);
	this->setVec3("lightColor", glm::vec3 { 1.0f });

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
