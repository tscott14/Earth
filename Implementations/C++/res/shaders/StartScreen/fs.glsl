#version 330 core

in vec2 vTexCoords;

out vec4 FragColor;

uniform sampler2D mTextureSampler;

void main()
{
    vec4 color = texture2D(mTextureSampler, vTexCoords);
    if (color.a < 0.5)
        discard;
    FragColor = color;
}
