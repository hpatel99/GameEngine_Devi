#ifndef _STRUCTS_H
#define _STRUCTS_H

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
#endif

