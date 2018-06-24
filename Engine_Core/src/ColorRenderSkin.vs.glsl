// COLOR RENDER - Vertex Shader
#version 400 core

layout (location = 0) in vec4 vVert;
layout (location = 1) in vec2 vTexCoord0;
layout (location = 2) in vec3 vNormal;
layout (location = 3) in vec4 vWeights;
layout (location = 4) in ivec4 bone;


in vec4 position;

out VS_OUT
{
    vec4 color;
} vs_out;

// Uniforms:
uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 inv[100];
uniform mat4 bit[100];

void main()
{              
	vec4 Pos =  bit[bone.x] * inv[bone.x]  * vVert * vWeights.x +
				bit[bone.y] * inv[bone.y] * vVert * vWeights.y +
				bit[bone.z] * inv[bone.z] * vVert * vWeights.z +
				bit[bone.w] * inv[bone.w] * vVert * vWeights.w;

				gl_Position = proj_matrix *view_matrix *Pos;
				//gl_Position = proj_matrix *view_matrix * world_matrix * vVert;
				vs_out.color = vWeights;
}