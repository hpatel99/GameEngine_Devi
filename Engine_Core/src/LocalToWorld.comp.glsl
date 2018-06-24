// Compute Shader Test
#version 430 core

layout(local_size_x = 20) in;

struct Bone
{
	vec4 translation;
	vec4 rotation;
	vec4 scale;
};

layout (std430, binding = 0) buffer LocalBoneMatrices
{
	Bone bonesIn[];
};

layout (std430, binding = 1) buffer HierarchyTable
{
	int boneTable[];
};

layout (std430, binding = 2) buffer InversePoseMatrices
{
	mat4 inverseMats[];
};

layout (std430, binding = 3) buffer BoneWorldXInverse
{
	mat4 outputMats[];
};

uniform int maxHierarchyDepth;
uniform int numBones;
uniform mat4 Rigidworld_matrix;

mat4 RotMatrix(vec4 quat);
mat4 TransMatrix(vec4 trans);
mat4 ScaleMatrix(vec4 scale);

void main()
{
	if (gl_GlobalInvocationID.x < numBones)
	{
		uint boneIndex = gl_GlobalInvocationID.x;
		int rowSize = maxHierarchyDepth;
		int columnIndex = 0;
		int parentIndex = 0;
		
		// Initialize to parentlocal index
		parentIndex = boneTable[boneIndex * rowSize + columnIndex];
		
		//initialize to the world of first
		mat4 boneWorld = Rigidworld_matrix;
		
		

		// Multiply the parent bone local matrices down the hierarchy to get the world matrix
		for (int colIndex = 0; colIndex < maxHierarchyDepth; ++colIndex)
		{
			parentIndex = boneTable[boneIndex * rowSize + colIndex];
			if (parentIndex != -1)
			{
				//mat4 parentLocal = TransMatrix(bonesIn[parentIndex].translation) * RotMatrix(bonesIn[parentIndex].rotation) * ScaleMatrix(bonesIn[parentIndex].scale);
				//boneWorld = boneWorld * parentLocal;
				
				boneWorld *= TransMatrix(bonesIn[parentIndex].translation) * RotMatrix(bonesIn[parentIndex].rotation) * ScaleMatrix(bonesIn[parentIndex].scale);
			}
			
		}

			//multiply with inverse bone matrix
			//outputMats[boneIndex-1] = boneWorld * inverseMats[boneIndex-1];
		outputMats[boneIndex] = boneWorld *inverseMats[boneIndex];
		
		
	}
	
};

mat4 RotMatrix(vec4 quat)
{
	float tmpX;
	float tmpY;
	float tmpZ;
	float tmpW;

	mat4 result;

	//Set row 1
	tmpX = 1 - 2 * (quat.y*quat.y + quat.z*quat.z);
	tmpY = 2 * (quat.x*quat.y + quat.w*quat.z);
	tmpZ = 2 * (quat.x*quat.z - quat.w*quat.y);
	tmpW = 0.0f;
	result[0] = vec4(tmpX, tmpY, tmpZ, tmpW);

	//Set row 2
	tmpX = 2 * (quat.x*quat.y - quat.w*quat.z);
	tmpY = 1 - 2 * (quat.x*quat.x + quat.z*quat.z);
	tmpZ = 2 * (quat.y*quat.z + quat.w*quat.x);
	tmpW = 0.0f;
	result[1] = vec4(tmpX, tmpY, tmpZ, tmpW);

	//Set row 3
	tmpX = 2 * (quat.x*quat.z + quat.w*quat.y);
	tmpY = 2 * (quat.y*quat.z - quat.w*quat.x);
	tmpZ = 1 - 2 * (quat.x*quat.x + quat.y*quat.y);
	tmpW = 0.0f;
	result[2] = vec4(tmpX, tmpY, tmpZ, tmpW);

	//Set row 4

	tmpX = 0.0f;
	tmpY = 0.0f;
	tmpZ = 0.0f;
	tmpW = 1.0f;
	result[3] = vec4(tmpX, tmpY, tmpZ, tmpW);

	return result;
}

mat4 TransMatrix(vec4 trans)
{
	mat4 result;
	result[0] = vec4(1.0, 0.0, 0.0, 0.0);
	result[1] = vec4(0.0, 1.0, 0.0, 0.0);
	result[2] = vec4(0.0, 0.0, 1.0, 0.0);
	result[3] = trans;

	return result;
}

mat4 ScaleMatrix(vec4 scale)
{
	mat4 result;
	result[0] = vec4(scale.x, 0.0, 0.0, 0.0);
	result[1] = vec4(0.0, scale.y, 0.0, 0.0);
	result[2] = vec4(0.0, 0.0, scale.z, 0.0);
	result[3] = vec4(0.0, 0.0, 0.0, 1.0);

	return result;
}