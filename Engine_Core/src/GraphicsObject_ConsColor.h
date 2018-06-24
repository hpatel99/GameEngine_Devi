#ifndef GRAPHICSOBJECT_CONST_COLOR
#define GRAPHICSOBJECT_CONST_COLOR
#include "GraphicsObject.h"

class GraphicsObject_ConstColor :public GraphicsObject
{
public:
	GraphicsObject_ConstColor(Model *model, ShaderObject *pShaderObj, Vect &LightColor, Vect &LightPos, Name inName);
	GraphicsObject_ConstColor() = delete;
	~GraphicsObject_ConstColor();

	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here
	Vect *pLightColor;
	Vect *pLightPos;

};
#endif
