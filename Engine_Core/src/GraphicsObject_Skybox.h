#ifndef GRAPHICS_OBJECT_SKYBOX_H
#define GRAPHICS_OBJECT_SKYBOX_H

#include "GraphicsObject.h"
#include "Texture.h"

class GraphicsObject_Skybox :public GraphicsObject
{
public:
	GraphicsObject_Skybox(Model *model, ShaderObject *pShaderObj, Texture::Name texname, Name inName);

	// Render material contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here
	Texture::Name textName;
};
#endif