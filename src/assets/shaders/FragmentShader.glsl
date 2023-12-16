#version 330 core

in vec2 UV;
// Ouput data
out vec3 color;

uniform sampler2D myTextureSampler;

void main()
{

	// Output color = red 
	color = texture(myTextureSampler, UV).rgb;
	

}