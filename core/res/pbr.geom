#version 450

layout(triangles) in;

layout(line_strip) out;
layout(max_vertices = 2) out;

in vec3 face_normal[];

uniform vec3 light_pos;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0); 
uniform mat4 ml_matrix = mat4(1.0);

void main(){
	int i;
	for(i = 0; i < gl_in.length(); ++i){
		vec3 P = gl_in[i].gl_Position.xyz;
		vec3 N = (pr_matrix * vw_matrix * vec4(face_normal[i], 1.0)).xyz;
		
		vec4 worldPosition = ml_matrix * vec4(P, 1.0);

		gl_Position = vec4(P, 1.0);
		EmitVertex();

		gl_Position = vec4(P + N * 0.1, 1.0);
		EmitVertex();
		EndPrimitive();

		gl_Position = vec4(P, 1.0);
		EmitVertex();

		vec3 light_dir = normalize(light_pos - worldPosition.xyz);
		gl_Position = vec4(P + light_dir * 0.1, 1.0);
		EmitVertex();
		EndPrimitive();
	}
	//EndPrimitive();
}