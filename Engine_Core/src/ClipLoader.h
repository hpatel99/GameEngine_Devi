#pragma once
#include "Clip.h"


class ClipLoader
{
public:
	static void Create();
	static Clip* Add(const char * const pModelFileName, Clip::Name inname);
private:
	ClipLoader();
	static ClipLoader *privInstance();
	static ClipLoader *pClipImporter;
	static void privCreate();
	static unsigned int ClipLoader::GetSize(const char *const &P);

};

