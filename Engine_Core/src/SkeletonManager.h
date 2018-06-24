#pragma once
#include "PCSTree.h"
#include "Skeleton.h"

class SkeletonManager
{
public:

	static void Create();
	static void Add(Skeleton *inNode);
	static void Update();
	static Skeleton* Find(Skeleton::Name inname);

	~SkeletonManager();

private:


	SkeletonManager();
	static SkeletonManager* privInstance();
	static SkeletonManager *pSkeletonManger;
	static void privCreate();
	Skeleton *pHead;
};

