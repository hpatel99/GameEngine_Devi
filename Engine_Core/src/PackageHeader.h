//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef PACKAGE_HEADER_H
#define PACKAGE_HEADER_H

struct PackageHeader
{
	static const unsigned int PACKAGE_VERSION_SIZE = 20;
	static const unsigned int PACKAGE_NAME_SIZE = 20;


	char			packageName[PACKAGE_NAME_SIZE];
	char			versionString[PACKAGE_VERSION_SIZE];
	unsigned int	numChunks;
	unsigned int	totalSize;   // size of file (without package header)
};

#endif