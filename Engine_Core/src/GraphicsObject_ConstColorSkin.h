#ifndef GRAPHICSOBJECT_CONST_COLOR_SKIN
#define GRAPHICSOBJECT_CONST_COLOR_SKIN
#include "GraphicsObject.h"
#include "Skeleton.h"
#include "Animation.h"

class GraphicsObject_ConstColorSkin :public GraphicsObject
{
public:
	GraphicsObject_ConstColorSkin(Model *model, ShaderObject *pShaderObj ,Skeleton *pSkeleton_ ,Animation* pInAnim ,Name inName);
	GraphicsObject_ConstColorSkin() = delete;
	~GraphicsObject_ConstColorSkin();

	// Rendermaterial contract
	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	// data:  place uniform instancing here
	Skeleton *p_skeleton;
	Animation *p_anim;

};
#endif
