#version 330 core

layout (location = 0) out vec4 FragColor;

void main() {
	vec3 objectColor = vec3(0.3f, 0.3f, 1.0f);
	vec3 lightColor = vec3( 1.0f );
	FragColor = vec4(objectColor * lightColor, 1.0f);
}
