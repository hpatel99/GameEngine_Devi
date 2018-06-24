#ifndef SPACE_MODEL_H
#define SPACE_MODEL_H
#include "Model.h"

class SpaceModel : public Model
{
public:

	SpaceModel(const char * const pModelFileName);
	
	SpaceModel() = delete;
	SpaceModel(const SpaceModel &) = delete;
	SpaceModel &operator=(const SpaceModel &) = delete;
	virtual ~SpaceModel();
private:
	virtual void privCreateVAO(const char * const modelfileNAME);

};
#endif // !Space_MODEL_H

