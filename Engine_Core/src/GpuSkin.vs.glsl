// COLOR RENDER - Vertex Shader
#version 430 core

layout (location = 0) in vec4 vVert;
layout (location = 1) in vec2 vTexCoord0;
layout (location = 2) in vec3 vNormal;
layout (location = 3) in vec4 vWeights;
layout (location = 4) in ivec4 bone;

layout (std430, binding = 0) buffer BoneWorldXInverseMatrices
{
	mat4 bonesWorldXInv[];
};

in vec4 position;

out VS_OUT
{
    vec4 color;
} vs_out;

// Uniforms:
uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
//uniform mat4 inv[100];
//uniform mat4 bit[100];

void main()
{              
	vec4 Pos =  bonesWorldXInv[bone.x]  * vVert * vWeights.x +
				bonesWorldXInv[bone.y] * vVert * vWeights.y +
				bonesWorldXInv[bone.z] * vVert * vWeights.z +
				bonesWorldXInv[bone.w] * vVert * vWeights.w;

				gl_Position = proj_matrix *view_matrix *Pos;
				//gl_Position = proj_matrix *view_matrix * world_matrix * vVert;
				vs_out.color = vWeights;
}