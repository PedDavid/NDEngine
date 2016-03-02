#version 440

layout (location = 0) out vec4 color;

in vec2 fTexCoords;

uniform int index;
uniform sampler2DArray textureSampler;

void main(){
	color = texture(textureSampler, vec3(fTexCoords, index));
}