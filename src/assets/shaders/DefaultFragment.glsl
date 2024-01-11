#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D myTextureSampler;

void main()
{
	vec3 tex_color = 
	color = texture(myTextureSampler, UV).rgb;
}