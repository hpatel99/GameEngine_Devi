#ifndef IMPORTED_MODEL_H
#define IMPORTED_MODEL_H
#include "Model.h"
#include "BoundingSphere.h"
class ImportedModel : public Model
{
public:

	ImportedModel(const char * const pModelFileName,Model::Name inName);
	ImportedModel(unsigned char *VertBuff,unsigned char *Tribuff,unsigned int vertsize,unsigned int trisize, Model::Name inName);
	ImportedModel() = delete;
	ImportedModel(const ImportedModel &) = delete;
	ImportedModel &operator=(const ImportedModel &) = delete;
	virtual ~ImportedModel();
private:
	virtual void privCreateVAO(const char * const modelfileNAME);
	virtual void privCreateVAO(unsigned char *VertBuff, unsigned char *Tribuff, unsigned int vertsize, unsigned int trisize);
};
#endif // !IMPORTED_MODEL_H