#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out vec3 pos;
out vec4 col;

void main(){
	col = color;
	vec4 aux = ml_matrix * vec4(position, 1.0);
	pos = aux.xyz;
	gl_Position = pr_matrix * ml_matrix * vec4(position, 1.0);
}