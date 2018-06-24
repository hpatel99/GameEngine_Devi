#ifndef PYRAMID_MODEL_H
#define PYRAMID_MODEL_H
#include "Model.h"
#include "MathEngine.h"

class PyramidModel : public Model
{
public:

	PyramidModel(const char * const pModelFileName);

	PyramidModel() = delete;
	PyramidModel(const PyramidModel &) = delete;
	PyramidModel &operator=(const PyramidModel &) = delete;
	virtual ~PyramidModel();
private:
	virtual void privCreateVAO(const char * const modelfileNAME);

};
#endif // !PYRAMID_MODEL_H

