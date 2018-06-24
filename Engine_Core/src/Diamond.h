#ifndef DIAMOND_MODEL_H
#define PYRAMID_MODEL_H
#include "Model.h"
class DiamondModel : public Model
{
public:

	DiamondModel(const char * const pModelFileName);

	DiamondModel() = delete;
	DiamondModel(const DiamondModel &) = delete;
	DiamondModel &operator=(const DiamondModel &) = delete;
	virtual ~DiamondModel();
private:
	virtual void privCreateVAO(const char * const modelfileNAME);

};
#endif // !DIAMOND_MODEL_H

