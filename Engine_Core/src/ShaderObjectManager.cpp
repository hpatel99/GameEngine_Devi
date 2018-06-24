#include "ShaderObjectManager.h"
#include "ShaderObject.h"
#include "PCSTreeForwardIterator.h"

ShaderObjectManager *ShaderObjectManager::pShaderObjectManager = 0;


void ShaderObjectManager::Add(PCSNode * inNode)
{	//HACK Fix this have you not heard about DRY
	assert(inNode != nullptr);
	ShaderObjectManager *pman = ShaderObjectManager::privInstance();
	PCSNode *pRoot = pman->pRootTree->GetRoot();
	pman->pRootTree->Insert(inNode, pRoot);
}

ShaderObject * ShaderObjectManager::Find(ShaderObject::Name inname)
{
	ShaderObjectManager *pman = ShaderObjectManager::privInstance();
	assert(pman);
	PCSNode *pRootNode = pman->pRootTree->GetRoot();

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	ShaderObject *pShader = nullptr, *pResult = nullptr;
	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		pShader = (ShaderObject*)pNode;
		if (pShader->name == inname)
		{
			pResult = pShader;
			break;
		}
		pNode = pForwardIter.Next();
	}
	return  pResult;
}

void ShaderObjectManager::Create()
{
	privCreate();
}

void ShaderObjectManager::LoadAllShaders()
{
	ShaderObject *pNull = new ShaderObject(ShaderObject::Name::NULL_SHADER, "nullRender");
	Add(pNull);

	ShaderObject *pShaderObj = new ShaderObject(ShaderObject::Name::Simple_Color, "colorRender");
	
	Add(pShaderObj);

	ShaderObject *pShaderObjTexture = new ShaderObject(ShaderObject::Name::Texture, "textureRender");
	
	Add(pShaderObjTexture);

	ShaderObject *pShaderObjSky = new ShaderObject(ShaderObject::Name::SKYBOX, "textureRender");

	Add(pShaderObjSky);

	ShaderObject *pShaderObjPointLight = new ShaderObject(ShaderObject::Name::POINTLIGHT_TEXTURE, "texturePointLightDiff");
	Add(pShaderObjPointLight);

	ShaderObject *pShaderObjconstColor = new ShaderObject(ShaderObject::Name::CONST_COLOR, "constcolorRender");
	Add(pShaderObjconstColor);
	
	 pShaderObjconstColor = new ShaderObject(ShaderObject::Name::TOON_SHADER, "toonshading");
	Add(pShaderObjconstColor);

	pShaderObj = new ShaderObject(ShaderObject::SINGLECOLOR_WIREFRAME, "colorSingleRender");
	Add(pShaderObj);

	pShaderObj = new ShaderObject(ShaderObject::SKINNING, "ColorRenderSkin");
	Add(pShaderObj);

	pShaderObj = new ShaderObject(ShaderObject::GPU_SKINNIG, "GpuSkin");
	Add(pShaderObj);

	//pShaderObj = new ShaderObject(ShaderObject::COMP_TEST, "computeTest",ShaderObject::Compute);
	//Add(pShaderObj);


	pShaderObj = new ShaderObject(ShaderObject::COMP_Interpolate, "Interpolate",ShaderObject::Compute);
	Add(pShaderObj);
	//initialze graphicsobject

	pShaderObj = new ShaderObject(ShaderObject::COMP_localtoworld, "LocalToWorld", ShaderObject::Compute);
	Add(pShaderObj);
	//initialze graphicsobject
}

ShaderObjectManager::ShaderObjectManager()
{
	this->pRootTree = new PCSTree();
	
	assert(pRootTree != nullptr);
}

ShaderObjectManager * ShaderObjectManager::privInstance()
{
	return pShaderObjectManager;
}

void ShaderObjectManager::privCreate()
{
	if (ShaderObjectManager::pShaderObjectManager == nullptr)
	{
		ShaderObjectManager::pShaderObjectManager = new ShaderObjectManager();
		
		assert(pShaderObjectManager);
	}
}
