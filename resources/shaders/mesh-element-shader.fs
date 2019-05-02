#version 330 core

const vec4 MAIN_COLOR = vec4(0.0f, 0.0f, 0.0f, 1.0f);
const vec4 SELECT_COLOR = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform bool isSelected;

void main() {
	gl_FragColor = isSelected ? SELECT_COLOR : MAIN_COLOR;
}
