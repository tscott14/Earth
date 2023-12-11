#version 330 core

in vec3 aPosition;
in vec2 aTexCoords;

out vec2 vTexCoords;

uniform mat4 uModel = mat4(1.0);
uniform mat4 uProj = mat4(1.0);

void main()
{
    gl_Position = uProj * uModel * vec4(aPosition, 1);
    vTexCoords = aTexCoords;
}
