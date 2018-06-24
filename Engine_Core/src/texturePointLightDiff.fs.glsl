#version 400 core

// Not allowed in 400, only 420
// layout (binding = 0) uniform sampler2D tex_object;

//uniform sampler2D tex_object;
//in VS_OUT
//{
//    vec2 textCoordinate;
//} fs_in;
//out vec4 color;
//void main(void)
//{
//    color = texture(tex_object, fs_in.textCoordinate );
//}

// Uniforms
	uniform sampler2D textureUnit0;

// Varying
	in VS_OUT
	{
		vec4 vFragColor;
		vec2 vTex;
	} fs_in;

	out vec4 color;

void main(void) 
{ 
	color = fs_in.vFragColor * texture(textureUnit0, fs_in.vTex);
}
