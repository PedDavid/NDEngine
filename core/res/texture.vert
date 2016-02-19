#version 440

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 vTexCoords;

out vec2 fTexCoords;

void main(){
	fTexCoords = vTexCoords;
	gl_Position = vec4(position, 0.0, 1.0);
}