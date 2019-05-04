#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

uniform struct MVP {
	mat4 model;
	mat4 view;
	mat4 projection;
} mvp;

void main(){
	gl_Position = (mvp.projection * mvp.view * mvp.model) * vec4(VertexPosition, 1.0f);
}
