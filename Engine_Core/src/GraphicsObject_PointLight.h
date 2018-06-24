#ifndef GRAPHICS_OBJECT_POINTLIGHT_H
#define GRAPHICS_OBJECT_POINTLIGHT_H
#include "GraphicsObject.h"
#include "Texture.h"

class GraphicsObject_PointLight : public GraphicsObject
{
public:
	GraphicsObject_PointLight(Model *model, ShaderObject *pShaderObj, Texture::Name  name, Vect &LightColor, Vect &LightPos,Name inname);
	GraphicsObject_PointLight() = delete;
	~GraphicsObject_PointLight();

	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;
	//void SwapTexture(GLuint innewid);
	// data:  place uniform instancing here

	Texture::Name textName;
	Vect *pLightColor;
	Vect *pLightPos;

};
#endif
