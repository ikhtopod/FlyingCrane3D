#include "Shader.h"


/*************************/
/* Start default shaders */

const std::string Shader::DEFAULT_VERTEX_SOURCE =
R"glsl(#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	FragPos = vec3( model * vec4(VertexPosition, 1.0) );
	Normal = VertexNormal;
	gl_Position = (projection * view * model) * vec4(VertexPosition, 1.0f);
}
)glsl";

const std::string Shader::DEFAULT_FRAGMENT_SOURCE =
R"glsl(#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

void main() {
	vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);
	vec3 lightColor = vec3( 1.0f );
	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	
	float diff = max( dot(norm, lightDir), 0.0 );
	vec3 diffuse = diff * lightColor;
	
	float ambientStrength = 1.0f;
	//vec3 ambientStrength = vec3(0.2f, 0.2f, 0.3f);
	vec3 ambient = lightColor * ambientStrength;

	vec3 objectColor = vec3(.7f, .3f, .0f);
	
	vec3 result = (ambient + diffuse) * objectColor;
	//vec3 result = ambient * objectColor;
	
	FragColor = vec4(result, 1.0f);
}
)glsl";

/* End default shaders */
/***********************/


Shader::Shader() : vertexSource(DEFAULT_VERTEX_SOURCE), fragmentSource(DEFAULT_FRAGMENT_SOURCE) {}

Shader::Shader(std::filesystem::path _vertexPath, std::filesystem::path _fragmentPath)
	: vertexPath(_vertexPath), fragmentPath(_fragmentPath),
	vertexSource(Util::getTextFromFile(vertexPath)),
	fragmentSource(Util::getTextFromFile(fragmentPath)) {}


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
	Application* appThis = Application::getInstancePtr();

	if (this->useMVP) {
		this->setMat4("model", appThis->getScene().getModel().getModel());
		this->setMat4("view", appThis->getScene().getModel().getView());
		this->setMat4("projection", appThis->getScene().getModel().getProjection());
	}

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
