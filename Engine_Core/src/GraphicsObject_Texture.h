#ifndef GRAPHICS_OBJECT_TEXTURE_H
#define GRAPHICS_OBJECT_TEXTURE_H

#include "GraphicsObject.h"
#include "Texture.h"

class GraphicsObject_Texture :public GraphicsObject
{
public:
	GraphicsObject_Texture(Model *model, ShaderObject *pShaderObj,Texture::Name texname,Name inName);

	// Render material contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;
	void ChangeTexName( Texture::Name iNnEW);
	// data:  place uniform instancing here
	Texture::Name textName;
};
#endif