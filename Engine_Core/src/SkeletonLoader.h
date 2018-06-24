#pragma once
#include "Skeleton.h"

class SkeletonLoader
{

public:

	static void Create();
	static void Add(const char * const pModelFileName,float size, const char * const pInverse ,Skeleton::Name inname);
private:
	SkeletonLoader();
	static SkeletonLoader *privInstance();
	static SkeletonLoader *pSkeletonImporter;
	static void privCreate();
	static unsigned int SkeletonLoader::GetSize(const char *const &P);
	
};

