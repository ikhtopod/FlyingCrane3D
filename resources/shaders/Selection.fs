#version 330 core

layout (location = 0) out vec4 FragColor;

uniform vec4 colorCode;

void main() {
    FragColor = vec4(colorCode.r, colorCode.g, colorCode.b, colorCode.a) / 255.0;
}
