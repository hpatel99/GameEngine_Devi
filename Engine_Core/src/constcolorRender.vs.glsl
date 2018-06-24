// CONST COLOR RENDER - Vertex Shader
#version 400 core

// Uniforms
	uniform mat4 world_matrix;
	uniform mat4 view_matrix;
	uniform mat4 proj_matrix;
	uniform vec3 vLightPos;
	uniform vec4 vColor;

// Attributes
	layout (location = 0) in vec4 vVert;
	layout (location = 2) in vec3 vNormal;

// Varying
	out VS_OUT
	{
		vec4 vFragColor;
	} vs_out;


void main(void) 
{ 
	// Get vNorm
		mat4 mvMatrix = view_matrix * world_matrix;
		mat3 mNormalMatrix;
		mNormalMatrix[0] = normalize(mvMatrix[0].xyz);
		mNormalMatrix[1] = normalize(mvMatrix[1].xyz);
		mNormalMatrix[2] = normalize(mvMatrix[2].xyz);
		vec3 vNorm = normalize(mNormalMatrix * vNormal);

	// Get vLightDir
		vec4 ecPosition;
		vec3 ecPosition3;
		ecPosition = mvMatrix * vVert;
		ecPosition3 = ecPosition.xyz /ecPosition.w;
		vec3 vLightDir = normalize(vLightPos - ecPosition3);

	// Get vFragColor
		float fDot = max(0.0, dot(vNorm, vLightDir)); 
		vs_out.vFragColor.rgb = vColor.rgb * fDot;
		vs_out.vFragColor.a = vColor.a;

	// Set Gl_position
		gl_Position = proj_matrix * view_matrix * world_matrix * vVert;
}