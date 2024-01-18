#version 330 core

in vec2 UV;
in vec4 gl_FragCoord;
in vec4 out_coord;
in float distance_to_camera;
// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;
uniform int torch;
uniform float mytime;
// uniform float visibilityRadius;
float Spotlight(vec3 lightPos, vec3 fragPos, vec3 spotDir, float cone, float decay)
{   
    vec3 lDir = normalize(lightPos - fragPos);
    float theta = dot(-lDir,spotDir);
    float dist = abs(length(lightPos - fragPos));
    float att = (1.0/(dist*dist));
    return clamp((theta-cone)/(decay),0.0,1.0)*clamp(att,0.0,1.0);
}



float linearizeDepth(float depth, float near, float far){
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
	float far = 1000.0;
	float near = 0.3;
	float depth = 0;
	float spot = 1.0;
	vec3 tex_color;
	vec3 light = vec3(1.0, 0.2, 0.0);
	vec3 light2 = vec3(1.0, 1.0, 1.0);

	// vec2 ms = vec2(0.0, 0.0);
	// vec3 lDir = normalize(vec3(ms.x,ms.y,1.0));
	// float phong = dot(lDir,vec3(0,0,1.0));
	// }else{
	// 	color = vec3(1.0, 0.0, 0.0);
	// }
	// float 
	// vec3 tex_color = texture(myTextureSampler, UV).rgb * depth;
	float radius = 5.0 + sin(cos(mytime*15) * cos(mytime*6.3)) * 0.1;

	if((torch == 1)||(torch == 3)){
		near = 0.2;
		depth = linearizeDepth(gl_FragCoord.z, near, far);	
		tex_color = texture(myTextureSampler, UV).rgb / depth;
		float puk = out_coord.z * out_coord.z + (out_coord.x-1.9) * (out_coord.x-1.9)  + out_coord.y * out_coord.y;
		if( puk < radius * radius){
			light = vec3((radius * radius - puk) * 1.0, (radius * radius - puk) * 0.5, 0.0);
			vec3 temp = mix(tex_color, light, (radius * radius - puk) * 0.4);
			color = vec4(tex_color * 0.9986 + temp * 0.0014, 1.0);
			// color = vec4(temp, 1.0);
		}else{
			color = vec4(tex_color, 1.0);
		}
		
		
		// spot = Spotlight(vec3(ms.x*0.53,ms.y*0.53,-0.2),
        //       		      vec3(gl_FragCoord.z,gl_FragCoord.z,0.0),
        //             	  lDir,
        //                   0.3,
        //                   0.2)*phong*1.3;
	}
	if((torch == 0)||(torch == 2)){
		near = 0.3;
		depth = linearizeDepth(gl_FragCoord.z, near, far);	
		tex_color = texture(myTextureSampler, UV).rgb / depth;
		color = vec4(tex_color, 1.0);
	}
	
	// color = vec4(tex_color, 1.0);
	// color = visibility;
	

}