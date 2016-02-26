#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 face_normal;
out vec3 light_dir;
out vec3 view_dir;

uniform vec3 light_pos;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0); 
uniform mat4 ml_matrix = mat4(1.0);

void main(){
	vec4 worldPosition = ml_matrix * vec4(position, 1.0);
	gl_Position = pr_matrix * vw_matrix * worldPosition;
	
	face_normal = normalize((ml_matrix * vec4(normal, 0.0)).xyz);
	light_dir = light_pos - worldPosition.xyz;
	view_dir = normalize((inverse(vw_matrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz);
}