#version 330

layout(triangles) in;

layout(triangle_strip) out;
layout(max_vertices = 3) out;

in vec3 face_normal[];

void main(){
	int i;
	for(i = 0; gl_in.length(); ++i){
		//vec3 P = gl_in[i].gl_Position.xyz;
		//vec3 N = face_normal[i];

		//gl_Position = vec4(P, 1.0);
		//EmitVertex();

		//gl_Position = vec4(P + N, 1.0);
		//EmitVertex();
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
		//EndPrimitive();
	}
	EndPrimitive();
}