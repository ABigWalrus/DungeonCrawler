#version 330 core

in vec2 UV;
in float visibility;
// Ouput data
out vec3 color;

uniform sampler2D myTextureSampler;
// uniform float visibilityRadius;

void main()
{

	// Output color = red 
	// if(visibility == 1){
		
		
	// }else{
	// 	color = vec3(1.0, 0.0, 0.0);
	// }
	vec3 tex_color = texture(myTextureSampler, UV).rgb;
	color = vec3(tex_color.x * visibility, tex_color.y * visibility, tex_color.z * visibility);
	// color = visibility;
	

}