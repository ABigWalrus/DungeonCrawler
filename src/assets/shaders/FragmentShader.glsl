#version 330 core

in vec2 UV;
in float visibility;
in vec4 gl_FragCoord;
// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;
// uniform float visibilityRadius;

float near = 0.3;
float far = 10000.0;

float linearizeDepth(float depth){
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0)*(far - near));
}
// float logisticDepth(float depth, float steepness = 0.5, float offset = 5.0){
// 	float zVal = linearizeDepth(depth);
// 	return (1/(1 + exp(-steepness * (zVal - offset))));
// }
void main()
{

	// Output color = red 
	// if(visibility == 1){
		
		
	// }else{
	// 	color = vec3(1.0, 0.0, 0.0);
	// }
	// float depth = logisticDepth(gl_FragCoord.z);
	// vec3 tex_color = texture(myTextureSampler, UV).rgb * depth;
	color = vec4(texture(myTextureSampler, UV).rgb / linearizeDepth(gl_FragCoord.z), 1.0);
	// color = visibility;
	

}