#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H


#include "ImportedModel.h"
#include "Texture.h"

#include "Skeleton.h"

class ModelImporter
{
public:
		
	static void Create();
	static void Add(const char * const pModelFileName,Model::Name inname,Texture::Name inTexname);
	static void AddSkinedModel(const char * const pskinfile,Model::Name inName);
private:
	ModelImporter();
	static ModelImporter *privInstance();
	static ModelImporter *pModelImporter;
	static void privCreate();
	static unsigned int GetSize(const char *const &P);

	//data memeber
};

#endif
