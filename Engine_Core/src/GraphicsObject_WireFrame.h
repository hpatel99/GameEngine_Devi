#ifndef GRAPHICS_OBJECT_WIREFRAME_H
#define GRAPHICS_OBJECT_WIREFRAME_H

#include "GraphicsObject.h"

class GraphicsObject_WireFrame :public GraphicsObject
{
public:
	GraphicsObject_WireFrame(Model *model, ShaderObject *pShaderObj,Name inName);

	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here

};
#endif