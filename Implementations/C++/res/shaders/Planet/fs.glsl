#version 410 core

in vec3 vNormalizedCoord_FS_in;
in vec3 vWorldNormalizedCoord_FS_in;
in vec3 vWorldTransformedCoord_FS_in;
in vec2 vTextureCoords_FS_in;

out vec4 FragColor;

uniform vec3 uSunDirection = vec3(0, 0, -1);

uniform sampler2D mAlbetoSampler;

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

float clamp(float src, float l, float u) {
    if(src < l) return l;
    if(src > u) return u;
    return src;
}

void main() {
    vec3 nNormal = normalize(vWorldNormalizedCoord_FS_in);
    float fact = dot(nNormal, -uSunDirection);
    fact = clamp(fact, 0.1, 1);

    //vec3 shading = GenerateTextureCoords(uBumpSampler2, vWorldTransformedCoord_FS_in, 1).xyz;
    //float s = Noise3FMB(vNormalizedCoord_FS_in);
    FragColor = fact * texture(mAlbetoSampler, vTextureCoords_FS_in * 4) * vec4(0.2, 0.7, 0.4, 1);
}