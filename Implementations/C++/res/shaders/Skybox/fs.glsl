#version 330 core

in vec3 vPosition;

out vec4 FragColor;

uniform samplerCube mAlbetoSampler;

void main() {
    FragColor = texture(mAlbetoSampler, vPosition); //vec4(0.8, 0.2, 0.8, 1.0);
}