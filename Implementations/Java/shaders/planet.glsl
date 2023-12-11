#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec3 aNormal;

out VS_OUT
{
	vec3 ToCameraVector;
	vec2 TextureCoords;
	mat3 TBN;
} vs_out;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

vec4 CalculateWorldTransform() {
	return uModel * vec4(aPos, 1.0);
}

vec4 CalculateVertexPosition(vec4 world_transform) {
	return uProj * uView * world_transform;
}

mat3 CalculateTBNMatrix() {
	vec3 T = normalize(vec3(uModel * vec4(aTangent,   0.0)));
	vec3 B = normalize(vec3(uModel * vec4(aBitangent, 0.0)));
	vec3 N = normalize(vec3(uModel * vec4(aNormal,    0.0)));
	return mat3(T, B, N);
}

vec3 CalculateCameraPosition() {
	vec4 result = inverse(uView) * vec4(0,0,0,1);
	return result.xyz;
}

void main() {
	vec4 world_transform = CalculateWorldTransform();
	gl_Position = CalculateVertexPosition(world_transform);
 	vs_out.TBN = CalculateTBNMatrix();
	vs_out.ToCameraVector = CalculateCameraPosition() - world_transform.xyz;
	vs_out.TextureCoords = aTexCoords;

}
			
<split>

#version 330 core

in VS_OUT
{
	vec3 ToCameraVector;
	vec2 TextureCoords;
	mat3 TBN;
} fs_in;

out vec4 albeto_output_color;

uniform vec3 uSunDirection;
uniform vec3 uSunColor;

uniform sampler2D uAlbetoTextureSampler;
uniform sampler2D uSpecularTextureSampler;
uniform sampler2D uNormalTextureSampler;

vec3 LoadAlbeto() {
	vec3 albeto = texture(uAlbetoTextureSampler, fs_in.TextureCoords).rgb;
	albeto *= 0.8; albeto += 0.1;
	return albeto;
}

vec3 LoadNormal() {
	vec3 normal = texture(uNormalTextureSampler, fs_in.TextureCoords).rgb;
	normal = normal * 2 - 1;
	normal.y *= dot(vec3(0,1,0), normal);
	return normalize((fs_in.TBN * normal));
}

vec3 LoadDiffuseLighting(vec3 nNormal, vec3 nSunDir) {
	float visability = dot(nNormal, nSunDir);
	float brightness = min(max(visability, 0.1), 1);

	//brightness /= brightness + 1;

	return uSunColor * brightness;
}

vec3 LoadSpecularLighting(vec3 nNormal, vec3 nSunDir) {
	float tSpecularMask = 1 - texture(uSpecularTextureSampler, fs_in.TextureCoords).r;
	tSpecularMask = min(max(tSpecularMask, 0.1), 0.9);

	vec3 reflectedLightDirection = reflect(-nSunDir, nNormal);
	reflectedLightDirection = normalize(reflectedLightDirection);

	vec3 nToCameraVector = normalize(fs_in.ToCameraVector);

	float specularFactor = dot(reflectedLightDirection, nToCameraVector);
	specularFactor = max(specularFactor, 0);

	float dampedFactor = pow(specularFactor,3);

	vec3 output_color = uSunColor * dampedFactor * tSpecularMask;
	//output_color /= output_color + 1;

	return output_color;
}

void main() {
	const float BRIGHTNESS = 0.25;
	const float GLARE = 0.1;

	vec3 tAlbeto = LoadAlbeto();

	vec3 nNormals = LoadNormal();
	vec3 nSunDirection = normalize(uSunDirection);

	vec3 diffuse = LoadDiffuseLighting(nNormals, nSunDirection);
	vec3 specular = LoadSpecularLighting(nNormals, nSunDirection);

	vec3 output_color = tAlbeto * diffuse * BRIGHTNESS + specular * GLARE;
	output_color /= output_color+1;

	albeto_output_color = vec4(output_color, 1);

}
