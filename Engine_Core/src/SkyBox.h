#ifndef SKYBOX_H
#define SKYBOX_H
#include "Model.h"
class SkyBox : public Model
{
public:

	SkyBox(const char * const pModelFileName);

	SkyBox() = delete;
	SkyBox(const SkyBox &) = delete;
	SkyBox &operator=(const SkyBox &) = delete;
	virtual ~SkyBox();
private:
	virtual void privCreateVAO(const char * const modelfileNAME);

};
#endif // !SKYBOX_H

