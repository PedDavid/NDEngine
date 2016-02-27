#version 450

layout(location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform vec3 light_pos;
 
out Vertex {
	vec3 normal;
} vertex;
 
void main() {
	gl_Position = vec4(position, 1.0);
	vertex.normal = normal;
}