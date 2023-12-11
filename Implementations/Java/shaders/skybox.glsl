#version 330 core

in vec3 aPos;

out VS_OUT
{
	vec3 TextureCoords;
} vs_out;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 proj = mat4(1.0);

void main() {
    vs_out.TextureCoords = aPos;
    vec4 pos = proj * view * model * vec4(aPos, 1.0);
    gl_Position = pos.xyww;

}
			
<split>

#version 330 core

in VS_OUT
{
	vec3 TextureCoords;
} fs_in;

out vec4 out_color;

uniform samplerCube skyboxSampler;

void main() {
	out_color = texture(skyboxSampler, fs_in.TextureCoords);
}
