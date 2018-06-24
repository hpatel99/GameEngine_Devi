// COLOR RENDER - Vertex Shader
#version 400 core

//in vec4 position;

//out VS_OUT
//{
//    vec4 color;
//} vs_out;

// Uniforms:
//uniform mat4 mv_matrix;
//uniform mat4 proj_matrix;

void main(void)
{              
	// Remember: We use ROW major, but OpenGL GLSL multiplies in reverse order!
  //  gl_Position = proj_matrix * mv_matrix * position;      

	// Position is the color + Grey
  //  vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}