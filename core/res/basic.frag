#version 440

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in vec4 pos;

void main(){
	float intensity = 1.0 / length(pos.xy - light_pos) * 0.10;
	color = vec4(0.2, 1.0, 1.0, 1.0) * intensity;
}