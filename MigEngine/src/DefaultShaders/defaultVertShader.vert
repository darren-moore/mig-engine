#version 330 core
layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

uniform mat4 texMap;

void main() {
    TexCoords = vec2(texMap * vec4(inTexCoord, 0.0, 1.0));
    gl_Position = projection * model * vec4(inPos, 0.0, 1.0);
}