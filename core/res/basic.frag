#version 440

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in vec4 pos;

void main(){
	float intensity = 1.0 / length(pos.xy - light_pos) * 0.1;
	//color = vec4(0.0, intensity, 0.0, 1.0);
	color = vec4(pos.x + 0.5, 0.0, 1.0, 1.0) * intensity;
}