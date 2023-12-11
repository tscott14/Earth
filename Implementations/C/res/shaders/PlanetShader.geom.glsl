#version 410 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 vWorldPosition_GS_in[];

out vec3 vWorldPosition_FS_in;
out vec3 vNormal_FS_in;



vec3 GenerateNormal() {
    vec3 p0 = vWorldPosition_GS_in[0];
    vec3 p1 = vWorldPosition_GS_in[1];
    vec3 p2 = vWorldPosition_GS_in[2];

    return cross(p2 - p0, p1 - p0);
}

void main() {
    vec3 normal = GenerateNormal();

    vWorldPosition_FS_in = vWorldPosition_GS_in[0];
    vNormal_FS_in = normal;
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    vWorldPosition_FS_in = vWorldPosition_GS_in[1];
    vNormal_FS_in = normal;
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    vWorldPosition_FS_in = vWorldPosition_GS_in[2];
    vNormal_FS_in = normal;
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}