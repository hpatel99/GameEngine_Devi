#ifndef GRAPHICS_OBJECT_TOONSHADER_H
#define GRAPHICS_OBJECT_TOONSHADER_H
#include "GraphicsObject.h"
#include "Texture.h"

class GraphicsObject_ToonShader :public GraphicsObject
{
public:
	GraphicsObject_ToonShader(Model *model, ShaderObject *pShaderObj, Name inName);

	// Render material contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here
	GLuint tex_toon;
};




#endif