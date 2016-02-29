#version 450

layout(triangles) in;
layout(line_strip, max_vertices=6) out;
 
uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0); 
uniform mat4 ml_matrix = mat4(1.0);

uniform vec3 light_pos;

mat4 mvp;
 
in Vertex {
	vec3 normal;
} vertex[];
 
vec4 light_color = vec4(1.0, 1.0, 0.0, 1.0);
vec4 normal_color = vec4(0.0, 0.0, 1.0, 1.0);
vec4 view_color = vec4(0.0, 1.0, 0.0, 1.0);

out vec4 vertex_color;
 
void main() {
	mat4 worldPos;
	mvp = pr_matrix * vw_matrix * ml_matrix;
	int i;
	for(i=0; i < gl_in.length(); i++) {
		vec3 P = gl_in[i].gl_Position.xyz;
		vec3 N = vertex[i].normal;
    
		gl_Position = mvp * vec4(P, 1.0);
		vertex_color = normal_color;
		EmitVertex();
    
		gl_Position = mvp * vec4(P + N * 1.0, 1.0);
		vertex_color = normal_color;
		EmitVertex();
    
		EndPrimitive();

		// Light vector

		vec4 worldPosition = mvp * vec4(P, 1.0);
		vec3 light_dir = normalize(light_pos - worldPosition.xyz);

		gl_Position = mvp * vec4(P, 1.0);
		vertex_color = light_color;
		EmitVertex();

		gl_Position = mvp * vec4(P + light_dir * 1.0, 1.0);
		vertex_color = light_color;
		EmitVertex();

		EndPrimitive();
		
		// View vector

		vec3 view_dir = -normalize((inverse(vw_matrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz);

		gl_Position = mvp * vec4(P, 1.0);
		vertex_color = view_color;
		EmitVertex();

		gl_Position = mvp * vec4(P + view_dir * 1.0, 1.0);
		vertex_color = view_color;
		EmitVertex();

		EndPrimitive();
	}
}