#version 330 core

in vec3 positions;
in vec2 textureCoordnates;

out VS_OUT
{
	vec2 TextureCoords;
} vs_out;

uniform mat4 transformation;

void main() {

	gl_Position = transformation * vec4(positions, 1.0);
	vs_out = textureCoordnates;

}

<split>

#version 330 core

in VS_OUT
{
	vec2 TextureCoords;
} fs_in;

out vec4 out_color;

uniform sampler2D textureSampler;

void main() {
	out_color = texture(textureSampler, fs_in.TextureCoords);
}
