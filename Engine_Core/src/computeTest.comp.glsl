// Compute Shader Test
#version 430 core

layout(local_size_x = 20) in;

layout (std430, binding = 0) buffer inputBuffer
{
	int inputValues[];
};

layout (std430, binding = 1) buffer resultBuffer
{
	int outputValues[];
};

void main()
{
	outputValues[gl_GlobalInvocationID.x] = inputValues[gl_GlobalInvocationID.x] + 1;
};

