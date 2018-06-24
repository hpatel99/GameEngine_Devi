#ifndef GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H
#define GRAPHICS_OBJECT_WIREFRAME_CONSTANT_COLOR_H

#include "GraphicsObject.h"

class GraphicsObject_WireframeConstantColor :public GraphicsObject
{
public:
	GraphicsObject_WireframeConstantColor(Model *model, ShaderObject *pShaderObj, Vect &wireColor,Name Inname);

	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;	
	virtual void Draw() override;
	virtual void RestoreState() override;

public:
// data:  place uniform instancing here
	Vect *pWireColor;
	void setcolor(Vect *incolor);
	GraphicsObject_WireframeConstantColor() = delete;

};
#endif