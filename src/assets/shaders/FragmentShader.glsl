#version 330 core

in vec3 pos_color;
// Ouput data
out vec3 color;

void main()
{

	// Output color = red 
	if(pos_color.x <= 0.5f && pos_color.z <= 0.5f){
		color = vec3(0.3f, 0.8f, 0.6f);
	}else{
		color = pos_color;
	}
	

}