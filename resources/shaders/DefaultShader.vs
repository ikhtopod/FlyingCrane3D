#version 330 core

/* start structs */

struct MVP {
	mat4 model;
	mat4 view;
	mat4 projection;
};

/* end structs */

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 FragPos;
out vec3 Normal;

uniform MVP mvp;
uniform mat4 transform;

void main() {
	FragPos = vec3( mvp.model * transform * vec4(VertexPosition, 1.0) );
	Normal = mat3( transpose(inverse(mvp.model * transform)) ) * VertexNormal;
	//gl_Position = (mvp.projection * mvp.view * mvp.model * transform) * vec4(VertexPosition, 1.0f);
	gl_Position = (mvp.projection * mvp.view) * vec4(FragPos, 1.0f);
}
