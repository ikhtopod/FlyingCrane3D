#version 330 core

uniform bool isSelectionProcess;
uniform bool isSelected;
uniform vec4 colorCode;

const vec4 MAIN_COLOR = vec4(0.3f, 0.7f, 0.0f, 1.0f);
const vec4 SELECT_COLOR = vec4(0.9f, 0.2f, 0.0f, 1.0f);


void main() {
	if (isSelectionProcess) {
		gl_FragColor = vec4(colorCode.r, colorCode.g, colorCode.b, colorCode.a) / 255.0;
	} else {
		gl_FragColor = isSelected ? SELECT_COLOR : MAIN_COLOR;
	}
}
