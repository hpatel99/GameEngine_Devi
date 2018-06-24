// Compute Shader Test
#version 430 core

layout(local_size_x = 20) in;

#define MATH_TOLERANCE 0.0005f

struct Bone
{
	vec4 translation;
	vec4 rotation;
	vec4 scale;
};

layout (std430, binding = 0) buffer KeyFrameA
{
	Bone bonesA[];
};

layout (std430, binding = 1) buffer KeyFrameB
{
	Bone bonesB[];
};

layout (std430, binding = 2) buffer LocalBoneMatrices
{
	Bone bonesOut[];
};

uniform int numBones;
uniform float lerpFactor;

vec4 slerp(vec4 src, vec4 tar, float slerpFactor);
bool isNonZero(float val, float tolerance);

void main()
{
	if (gl_GlobalInvocationID.x < numBones)
	{
			bonesOut[gl_GlobalInvocationID.x].translation = mix(bonesA[gl_GlobalInvocationID.x].translation, bonesB[gl_GlobalInvocationID.x].translation, lerpFactor);
			bonesOut[gl_GlobalInvocationID.x].scale = mix(bonesA[gl_GlobalInvocationID.x].scale, bonesB[gl_GlobalInvocationID.x].scale, lerpFactor);
			bonesOut[gl_GlobalInvocationID.x].rotation = slerp(bonesA[gl_GlobalInvocationID.x].rotation, bonesB[gl_GlobalInvocationID.x].rotation, lerpFactor);
		
	}
};



vec4 slerp(vec4 src, vec4 tar, float slerpFactor)
{
	vec4 result = vec4(0.0, 0.0, 0.0, 0.0);

	// get cos(angle)
	float tmpCos = dot(src, tar);

	//If angle between src and tar is too big, rotate other way around
	if (tmpCos < 0)
	{
		tmpCos = -tmpCos;
		tar = -tar;
	}

	// get actual angle
	float rotAngle = acos(tmpCos);

	if ( isNonZero(rotAngle, MATH_TOLERANCE))
	{
		result = (src * (sin((1 - slerpFactor)*rotAngle) / sin(rotAngle)))
			+ (tar * (sin(slerpFactor*rotAngle) / sin(rotAngle)));
	}
	else
	{
		result = src;
	}

	// normalize the result quat
	if ( isNonZero(length(result), MATH_TOLERANCE) )
	{
		normalize(result);
	}

	return result;
}

bool isNonZero(float val, float tolerance)
{
	return ((val < -tolerance) || (val > tolerance));
}

