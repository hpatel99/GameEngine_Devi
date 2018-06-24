#include <sb7.h>
#include <assert.h>

#include "NullModel.h"


NullModel::NullModel(const char * const modelFileName)
	: Model(Model::Name::Null_Object)
{
	UNUSED_VAR(modelFileName);
}

NullModel::~NullModel()
{
	// remove anything dynamic here
}

void NullModel::privCreateVAO(const char * const modelFileName)
{
	UNUSED_VAR(modelFileName);
}

