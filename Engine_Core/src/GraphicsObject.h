#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"


#include "ShaderObject.h"
class Model;

class RenderMaterial :public PCSNode
{
protected:
	virtual void SetState() = 0;
	virtual void SetDataGPU() = 0;
	virtual void Draw() = 0;
	virtual void RestoreState() = 0;

};

class GraphicsObject : public RenderMaterial
{
public:
	enum Name
	{
		NOT_INITIALZED,

		CUBE_NULL,
		
		CUBE_SIMPLECOLOR,
		CUBE_CONSTCOLOR,
		CUBE_WIREFRAME,
		CUBE_TEXTURE_Duck,
		CUBE_TEXTURE_Brick,
		CUBE_TEXTURE_stones,
		CUBE_POINTLIGHT_duck,
		CUBE_POINTLIGHT_stones,
		CUBE_POINTLIGHT_Brick,
		CUBE_TOON,

		SPACE_FRIGATE_POINTLIGHT,
		ASTROBOY_POINTLIGHT,
		BUGGY_POINTLIGHT,
		WARBEAR_POINTLIGHT,
		GETH_WARRIOR,
		SPHERE_WIREFRAME,
		CAMERAMODEL_WIREFRAME,

		SPACE_FRIGATE_POINTLIGHT2,
		ASTROBOY_POINTLIGHT2,
		BUGGY_POINTLIGHT2,
		WARBEAR_POINTLIGHT2,
		WARBEAR_POINTLIGHT3,
		WARBEAR_POINTLIGHT4,
		GETH_WARRIOR2,

		SKINNIG_MODEL,
		SKINNING_HUMAN_PUNCH,
		SKINNING_HUMAN_SHOT,
		SKINNING_TEDDY_IDLE,
		SKINNING_TEDDY_WALK,
		PYRAMID_POINTLIGHT_duck,


		SKYBOX_TEXTURE


	};

	GraphicsObject(Model *model, ShaderObject *pShaderObj,Name inName = Name::NOT_INITIALZED);

	GraphicsObject() = delete;
	virtual ~GraphicsObject();

	void Render();
	void SetWorld(Matrix &_world);

	Model *GetModel() const;
	Matrix &GetWorld();

protected:
	Model			*pModel;
	Matrix			*pWorld;
	ShaderObject	*pShaderObj;
public:
	Name			name;


};
#endif