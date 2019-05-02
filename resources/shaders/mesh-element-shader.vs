#version 330 core

/* start structs */

struct MVP {
	mat4 model;
	mat4 view;
	mat4 projection;
};

/* end structs */

layout (location = 0) in vec3 VertexPosition;

uniform MVP mvp;
uniform mat4 transform;

void updatePointSize() {
	vec4 cp = mvp.view[3];
	float dist = distance(gl_Position.xyz, cp.xyz);
	float psize = clamp(200.0 / dist, 1.0, 8.0);
	gl_PointSize = psize;
}

void main() {
	gl_Position = mvp.projection * mvp.view * mvp.model * transform * vec4(VertexPosition, 1.0f);
	
	updatePointSize();
}
