#version 330

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 offset;

uniform mat4 pr_matrix;
uniform mat4 ml_matrix = mat4(1.0);

out vec4 col;

void main(){
	gl_Position = pr_matrix * ml_matrix * vec4(position + offset, 0.0, 1.0);
}