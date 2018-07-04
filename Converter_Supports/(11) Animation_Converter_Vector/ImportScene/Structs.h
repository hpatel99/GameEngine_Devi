#ifndef _STRUCTS_H
#define _STRUCTS_H
#include <vector>
#include "MathEngine.h"
class Quat;
class Vect;

struct ParentChildIndex
{
	char NodeName[32];
	int myIndex;
	int parentIndex;
};

struct BoneHeader
{
	int Numbones;
	int MaxDepth;
};
struct SkinHeader
{
	int NumOfVerts;
	int NumOfTris;

};

struct WeightTuple
{
	int index;
	float weight;
	bool operator < (const WeightTuple& othr)const
	{
		return (weight < othr.weight);
	}
};
struct FBX_Trilist
{
	int v0;
	int v1;
	int v2;
};
struct TableEntry
{
	std::vector<int>Hier;
};
struct Vert_xyzuvn		//moved it here so all model can inherit
{
	float x;
	float y;
	float z;
	float u;
	float v;
	float nx;
	float ny;
	float nz;
	bool operator == (const Vert_xyzuvn &b)
	{
		return(
			(this->x == b.x) &&
			(this->y == b.y) &&
			(this->z == b.z) &&

			(this->u == b.u) &&
			(this->v == b.v) &&

			(this->ny == b.ny) &&
			(this->ny == b.ny) &&
			(this->ny == b.ny)

			);
	}
};
struct VertInfo
{
	Vert_xyzuvn vert;
	int controlpointindex;

	bool operator == (const VertInfo& b)
	{
		return (
			(this->vert == b.vert) &&
			(this->controlpointindex == b.controlpointindex)
			);
	}

};
struct BoneIndex
{
	int Index[4];
};
struct BoneWeight
{
	float Index[4];
};


struct SkinVerts
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	std::vector<WeightTuple> Weight;


};



struct ClipHeader
{
	char Clipname[32];
	int numofFrames;

};

struct FrameBucketNodes
{
	int KeyFrameTime;
	unsigned int numBones;

};
struct FrameBoneNodes:public Align16
{
	Vect Translation;
	Quat Rotation;
	Vect Scale;

	int boneIndex;
	int KeytFrameTime;
	char pad[8];
	
};
struct Frame
{
	bool TobeKept = true;
	FrameBucketNodes Bucketnode;
	std::vector<FrameBoneNodes> BonesInFrame;		//wanted to hard set to 80 but .... not required i guess

	Frame()
	{
		BonesInFrame.reserve(80);
	}
};
#endif

