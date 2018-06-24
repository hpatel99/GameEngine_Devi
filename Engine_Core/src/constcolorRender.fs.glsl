#version 400 core


// Varying
	in VS_OUT
	{
		vec4 vFragColor;

	} fs_in;

	out vec4 color;

void main(void) 
{ 
	vec4 baseColor = vec4(0.0f,1.0f,0.0f,1.0f);
	color = fs_in.vFragColor * baseColor ;
}
