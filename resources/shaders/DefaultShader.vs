#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 FragPos;
out vec3 Normal;

uniform struct MVP {
	mat4 model;
	mat4 view;
	mat4 projection;
} mvp;

void main(){
	FragPos = vec3( mvp.model * vec4(VertexPosition, 1.0) );
	Normal = mat3( transpose(inverse(mvp.model)) ) * VertexNormal;
	//gl_Position = (mvp.projection * mvp.view * mvp.model) * vec4(VertexPosition, 1.0f);
	gl_Position = (mvp.projection * mvp.view) * vec4(FragPos, 1.0f);
}
