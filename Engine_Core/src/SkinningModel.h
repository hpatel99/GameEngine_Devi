#ifndef SKINNED_MODEL_H
#define SKINNED_MODEL_H
#include "Model.h"
class SkinnedModel : public Model
{
public:
	//SkinnedModel(const char * const pModelFileName, Model::Name inName);
	SkinnedModel(unsigned char *VertBuff, unsigned char *Tribuff,unsigned char* BoneIdx,unsigned char * Boneweight, int numverts,int numtris,Model::Name inName);
	
	
	SkinnedModel() = delete;
	SkinnedModel(const SkinnedModel &) = delete;
	SkinnedModel &operator=(const SkinnedModel &) = delete;
	
	virtual ~SkinnedModel();
	Matrix *WorldInverse;

private:
		virtual void privCreateVAO(const char * const modelfileNAME);
		void privCreateVAO(unsigned char *VertBuff, unsigned char *Tribuff, unsigned char* BoneIdx, unsigned char * Boneweight, int numverts, int numtris);

};



#endif
