#ifndef SPHERE_MODEL_H
#define SPHERE_MODEL_H
#include "Model.h"

class SphereModel : public Model
{
public:
	SphereModel(const char * const pModelFileName);
	virtual ~SphereModel();

	SphereModel() = delete;
	SphereModel(const SphereModel &) = delete;
	SphereModel &operator=(const SphereModel &) = delete;

private:
	virtual void privCreateVAO(const char * const modelfileNAME);


};


#endif
