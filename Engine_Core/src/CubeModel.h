#ifndef CUBE_MODEL_H
#define CUBE_MODEL_H
#include "Model.h"
class CubeModel : public Model
{
public:
	
	CubeModel(const char * const pModelFileName);

	CubeModel()=delete;
	CubeModel(const CubeModel &) = delete;
	CubeModel &operator=(const CubeModel &) = delete;
	virtual ~CubeModel();
private:
	virtual void privCreateVAO(const char * const modelfileNAME);
	
};
#endif // !CUBE_MODEL_H

