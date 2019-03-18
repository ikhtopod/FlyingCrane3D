#include "Shader.h"


const std::string Shader::SHADER_DIRECTORY { R"(..\resources\shaders)" };
const Shader::FsPath Shader::DEFAULT_VERTEX_PATH { Shader::SHADER_DIRECTORY + R"(\DefaultShader.vs)" };
const Shader::FsPath Shader::DEFAULT_FRAGMENT_PATH { Shader::SHADER_DIRECTORY + R"(\DefaultShader.fs)" };


Shader::Shader() : Shader(DEFAULT_VERTEX_PATH, DEFAULT_FRAGMENT_PATH) {}

Shader::Shader(FsPath _vertexPath, FsPath _fragmentPath)
	: vertexPath(_vertexPath), fragmentPath(_fragmentPath),
	vertexSource(Util::getTextFromFile(vertexPath)),
	fragmentSource(Util::getTextFromFile(fragmentPath)) {

	this->lambdaDraw = [](Shader* _this) {
		Application* appThis = Application::getInstancePtr();
		_this->setVec3("bgColor", glm::vec3 { appThis->getBgColor() });
		_this->setVec3("lightColor", glm::vec3 { 1.0f });
		_this->setVec3("objectColor", glm::vec3 { .7f, .3f, .0f });
		_this->setVec3("cameraPos", appThis->getScene().getCamera().getTransform().getPosition().getValue());
	};
}


void Shader::setLambdaDraw(LambdaDraw _lambdaDraw) {
	if (_lambdaDraw != nullptr) {
		this->lambdaDraw = _lambdaDraw;
	}
}

void Shader::resetLambdaDraw() {
	this->lambdaDraw = [](Shader* _this) {};
}


bool Shader::getUseMVP() {
	return this->useMVP;
}

void Shader::setUseMVP(bool _useMVP) {
	this->useMVP = _useMVP;
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
	glUseProgram(this->id);

	Application* appThis = Application::getInstancePtr();

	if (this->useMVP) {
		this->setMat4("mvp.model", appThis->getScene().getModel().getModel());
		this->setMat4("mvp.view", appThis->getScene().getModel().getView());
		this->setMat4("mvp.projection", appThis->getScene().getModel().getProjection());
	}

	this->lambdaDraw(this);
}

void Shader::free() {
	glDeleteShader(this->vertex);
	glDeleteShader(this->fragment);
	glDeleteProgram(this->id);
}


/* Exceptions */

ShaderException::ShaderException(char const* const message)
	: std::exception(message) {}
