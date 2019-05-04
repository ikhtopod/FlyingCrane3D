#version 330 core

const vec4 MAIN_COLOR = vec4(0.0f, 0.0f, 0.0f, 1.0f);
const vec4 SELECT_COLOR = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform bool isSelectionProcess;
uniform bool isSelected;
uniform vec4 colorCode;

void main() {
	if (isSelectionProcess) {
		gl_FragColor = vec4(colorCode.r, colorCode.g, colorCode.b, colorCode.a) / 255.0;
	} else {
		gl_FragColor = isSelected ? SELECT_COLOR : MAIN_COLOR;
	}
}
