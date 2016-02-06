#version 330

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in vec3 pos;
in vec4 col;

void main(){
	float intensity = 1.0 / length(pos.xy - light_pos);
	color = col * intensity;
}