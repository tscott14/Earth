#version 430 core

layout (quads) in;

uniform mat4 uReverse_ModelMatrix = mat4(1.0);
uniform mat4 uViewMatrix = mat4(1.0);
uniform mat4 uProjMatrix = mat4(1.0);

in vec3 vWorldPosition_ES_in[];
in vec2 vTextureCoords_ES_in[];

out vec3 vNormalizedCoord_FS_in;
out vec3 vWorldNormalizedCoord_FS_in;
out vec3 vWorldTransformedCoord_FS_in;
out vec2 vTextureCoords_FS_in;

float hash( float n )
{
    return fract(sin(n)*43758.5453);
}

float lerp(float a, float b, float f) {
    return a + (b - a) * f;
}

float Noise3Value( vec3 x )
{
    // The noise function returns a value in the range -1.0f -> 1.0f

    vec3 p = floor(x);
    vec3 f = fract(x);

    f       = f*f*(3.0-2.0*f);
    float n = p.x + p.y*57.0 + 113.0*p.z;

    return lerp(lerp(lerp( hash(n+0.0), hash(n+1.0),f.x),
                   lerp( hash(n+57.0), hash(n+58.0),f.x),f.y),
               lerp(lerp( hash(n+113.0), hash(n+114.0),f.x),
                   lerp( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
}

float Noise3FMB(vec3 pos) {
    float s = 0;
    float accum = 0;
    for(int o = 0; o < 6; o++) {
        float scale = pow(2, o);
        float weight = 1 / scale;
        accum += weight;
        s += weight * Noise3Value(pos * 25 * scale);
    }
    return s / accum;
}

vec4 GenerateTextureCoords(sampler2D samp, vec3 pos, float scale) {
    vec2 xy = pos.xy * scale;
    vec2 xz = pos.xz * scale;
    vec2 yz = pos.yz * scale;

    vec3 blending = abs(pos);
    blending = normalize(max(blending, 0.00001));
    float b = (blending.x + blending.y + blending.z);
    blending /= vec3(b,b,b);

    vec4 xaxis = texture(samp, yz);
    vec4 yaxis = texture(samp, xz);
    vec4 zaxis = texture(samp, xy);

    vec4 tex = xaxis * blending.x + yaxis * blending.y + zaxis * blending.z;

    return vec4(tex.xyz, 1);
}

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2, vec2 v3)
{
    vec2 p0 = mix(v0, v3, gl_TessCoord.x);
    vec2 p1 = mix(v1, v2, gl_TessCoord.x);
    vec2 p2 = mix(p0, p1, gl_TessCoord.y);
    return p2;
    //return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2, vec3 v3)
{
    vec3 p0 = mix(v0, v3, gl_TessCoord.x);
    vec3 p1 = mix(v1, v2, gl_TessCoord.x);
    vec3 p2 = mix(p0, p1, gl_TessCoord.y);
    return p2;

    //return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

#define USE_TRANSFORM false

void main() {
    vec3 pos = interpolate3D(vWorldPosition_ES_in[0],
                            vWorldPosition_ES_in[1],
                            vWorldPosition_ES_in[2], 
                            vWorldPosition_ES_in[3]);

    vec2 tc = interpolate2D(vTextureCoords_ES_in[0], 
                            vTextureCoords_ES_in[1], 
                            vTextureCoords_ES_in[2], 
                            vTextureCoords_ES_in[3]);
                                    
    vWorldNormalizedCoord_FS_in = pos;
    vTextureCoords_FS_in = tc;

    vec3 orginal_pos = (uReverse_ModelMatrix * vec4(pos, 1)).xyz;
    float scale = Noise3FMB(orginal_pos) * 0.1 + 0.9;
    vWorldTransformedCoord_FS_in = orginal_pos * scale;
    vNormalizedCoord_FS_in = orginal_pos;

    vec3 final_transform = int(USE_TRANSFORM) * pos * scale + int(!USE_TRANSFORM) * pos;
    gl_Position = uProjMatrix * uViewMatrix * vec4(final_transform, 1.0);
}