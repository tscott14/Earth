#version 330 core

layout(location=0) in vec3 aPosition;

out vec3 vPosition;

uniform mat4 uModelMatrix = mat4(1.0);
uniform mat4 uViewMatrix = mat4(1.0);
uniform mat4 uProjMatrix = mat4(1.0);

void main() 
{
    vPosition = aPosition;
    vec4 pos = uProjMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1);
    gl_Position = pos.xyww;

}