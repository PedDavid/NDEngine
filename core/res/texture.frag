#version 440

layout (location = 0) out vec4 color;

in vec2 fTexCoords;

uniform sampler2D textureSampler;

void main(){
	color = texture(textureSampler, fTexCoords);
}