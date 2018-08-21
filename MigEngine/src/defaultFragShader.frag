#version 330 core
out vec4 FragColor;

uniform vec3 shaderColor;

void main() {
	FragColor = vec4(shaderColor, 1.0);
}
