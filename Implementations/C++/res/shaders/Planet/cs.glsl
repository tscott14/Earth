#version 410 core

layout (vertices = 4) out;

in vec3 vWorldPosition_CS_in[];
in vec2 vTextureCoords_CS_in[];

out vec3 vWorldPosition_ES_in[];
out vec2 vTextureCoords_ES_in[];

uniform vec3 uCameraPosition = vec3(0,1.5,0);

float GetOuterTess(float src) {
    float altitude = length(uCameraPosition) - 1;
    float A = 1.0;
    float S = 2.0;
    return S / (A * altitude * altitude);
}

float GetInnerTess(float src) {
    float A = 0;
    float B = 1;
    float C = 0;
    float S = 3;
    return S / (A * src * src + B * src + C);
}

void main() {
    vec3 npos = normalize(vWorldPosition_CS_in[gl_InvocationID]);
    vWorldPosition_ES_in[gl_InvocationID] = npos;
    vTextureCoords_ES_in[gl_InvocationID] = vTextureCoords_CS_in[gl_InvocationID];

    if(dot(npos, normalize(uCameraPosition)) < 0.0) {
       gl_TessLevelOuter[0] = 0;
        gl_TessLevelOuter[1] = 0;
        gl_TessLevelOuter[2] = 0;
        gl_TessLevelInner[0] = gl_TessLevelOuter[2];
        return;  
    } 

    vec3 transformedPosition0 = npos;
    vec3 transformedPosition1 = npos;
    vec3 transformedPosition2 = npos;
    vec3 transformedPosition3 = npos;

    float distFromCamera0 = distance(uCameraPosition, transformedPosition0);
    float distFromCamera1 = distance(uCameraPosition, transformedPosition1);
    float distFromCamera2 = distance(uCameraPosition, transformedPosition2);
    float distFromCamera3 = distance(uCameraPosition, transformedPosition3);

    float maxEdge0 = (distFromCamera0 + distFromCamera1) / 2.0;
    float maxEdge1 = (distFromCamera0 + distFromCamera3) / 2.0;
    float maxEdge2 = (distFromCamera2 + distFromCamera3) / 2.0;
    float maxEdge3 = (distFromCamera1 + distFromCamera2) / 2.0;

    float edgeTess0 = GetOuterTess(maxEdge0);
    float edgeTess1 = GetOuterTess(maxEdge1);
    float edgeTess2 = GetOuterTess(maxEdge2);
    float edgeTess3 = GetOuterTess(maxEdge3);

    float minEdgeVertex = (
        distFromCamera0 + distFromCamera1 +
        distFromCamera2 + distFromCamera3
    ) / 4;

    float innerTess = GetInnerTess(minEdgeVertex);

    gl_TessLevelOuter[0] = edgeTess0;
    gl_TessLevelOuter[1] = edgeTess1;
    gl_TessLevelOuter[2] = edgeTess2;
    gl_TessLevelOuter[3] = edgeTess3;
    gl_TessLevelInner[0] = innerTess;
    gl_TessLevelInner[1] = innerTess;
}