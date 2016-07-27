#version 440

#extension GL_ARB_bindless_texture : require

layout (location = 0) out vec4 color;

in vec2 fTexCoords;

uniform int index;
layout(location = 0, bindless_sampler) uniform sampler2DArray tex;

void main(){
	color = texture(tex, vec3(fTexCoords, index));
}