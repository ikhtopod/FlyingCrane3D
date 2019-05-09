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

void updatePointSize() {
	vec4 cp = mvp.view[3];
	float dist = distance(gl_Position.xyz, cp.xyz);
	float psize = clamp(200.0 / dist, 1.0, 8.0);
	gl_PointSize = psize;
}

void main() {
	FragPos = vec3( mvp.model * transform * vec4(VertexPosition, 1.0f) );
	Normal = mat3( transpose(inverse(mvp.model * transform)) ) * VertexNormal;
	gl_Position = (mvp.projection * mvp.view) * vec4(FragPos, 1.0f);
	
	updatePointSize();
}
