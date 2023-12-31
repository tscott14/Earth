#version 410 core

layout (location = 0) in vec3 aPosition_VS_in;

uniform mat4 uModelMatrix = mat4(1.0);

out vec3 vWorldPosition_CS_in;

void main() {
    vWorldPosition_CS_in = (uModelMatrix * vec4(aPosition_VS_in, 1)).xyz;
}