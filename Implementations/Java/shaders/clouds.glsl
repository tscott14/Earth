#version 330 core

layout(location=0) in vec3 positions;
layout(location=1) in vec3 normals;
layout(location=2) in vec2 textureCoordnates;

out vec3 pass_normals;
out vec2 pass_textureCoordnates;

out VS_OUT
{
	vec3 Normals;
	vec2 TextureCoords;
} vs_out;


uniform mat4 model;
uniform mat4 view; 
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(positions * 1.01, 1);

 	vec4 new_normal = model * vec4(normals, 0); 
	vs_out.Normals = new_normal.xyz;

	vs_out.TextureCoords = textureCoordnates;
}


<split>	

#version 330 core
in vec3 pass_normals;
in vec2 pass_textureCoordnates;

in VS_OUT
{
	vec3 Normals;
	vec2 TextureCoords;
} fs_in;

out vec4 out_color;

uniform vec3 uSunDirection;
uniform vec3 uSunColor;

uniform sampler2D uAlbetoTextureSampler;

void main() {
	vec3 normalizedNormals = normalize(fs_in.Normals);
	vec3 normalizedSunDirection = normalize(uSunDirection);

	float lightup_factor = max(dot(normalizedNormals, normalizedSunDirection), 0.05);
	vec3 finalColor = uSunColor * lightup_factor;
	finalColor /= finalColor + 1;
	vec4 output_color = texture(uAlbetoTextureSampler, fs_in.TextureCoords) * vec4(finalColor, 1);
	output_color.a = (output_color.r + output_color.g + output_color.b) / 3.0;
	out_color = output_color;
}
