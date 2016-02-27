#version 450

layout(triangles) in;
layout(line_strip, max_vertices=6) out;
 
uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0); 
uniform mat4 ml_matrix = mat4(1.0);

uniform vec3 light_pos;

mat4 gxl3d_ModelViewProjectionMatrix;
 
in Vertex {
	vec3 normal;
} vertex[];
 
vec4 light_color = vec4(1.0, 1.0, 0.0, 1.0);
vec4 normal_color = vec4(0.0, 0.0, 0.0, 1.0);

out vec4 vertex_color;
 
void main() {
	mat4 worldPos;
	gxl3d_ModelViewProjectionMatrix = pr_matrix * vw_matrix * ml_matrix;
	int i;
	for(i=0; i < gl_in.length(); i++) {
		vec3 P = gl_in[i].gl_Position.xyz;
		vec3 N = vertex[i].normal;
    
		gl_Position = gxl3d_ModelViewProjectionMatrix * vec4(P, 1.0);
		vertex_color = normal_color;
		EmitVertex();
    
		gl_Position = gxl3d_ModelViewProjectionMatrix * vec4(P + N * 1.0, 1.0);
		vertex_color = normal_color;
		EmitVertex();
    
		EndPrimitive();

		vec4 worldPosition = gxl3d_ModelViewProjectionMatrix * vec4(P, 1.0);
		vec3 light_dir = normalize(light_pos - worldPosition.xyz);

		gl_Position = gxl3d_ModelViewProjectionMatrix * vec4(P, 1.0);
		vertex_color = light_color;
		EmitVertex();

		gl_Position = gxl3d_ModelViewProjectionMatrix * vec4(P + light_dir * 1.0, 1.0);
		vertex_color = light_color;
		EmitVertex();

		EndPrimitive();
	}
}