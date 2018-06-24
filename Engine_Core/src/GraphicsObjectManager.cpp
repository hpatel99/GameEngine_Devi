#include "GraphicsObjectManager.h"
#include "PCSTreeForwardIterator.h"
#include "GraphicsObject_Null.h"
#include "GraphicsObject_PointLight.h"
#include "ModelManager.h"
#include "ShaderObjectManager.h"
#include "GraphicsObject_Skybox.h"
#include "GraphicsObject_WireframeConstantColor.h"

GraphicsObjectManager *GraphicsObjectManager::pGraphicsObjectManager = 0;
void GraphicsObjectManager::Add(PCSNode * inNode)
{
	assert(inNode != nullptr);
	GraphicsObjectManager *pman = GraphicsObjectManager::privInstance();
	PCSNode *pRoot = pman->pRootTree->GetRoot();
	pman->pRootTree->Insert(inNode, pRoot);
}

GraphicsObject * GraphicsObjectManager::Find(GraphicsObject::Name inName)
{
	GraphicsObjectManager *pman = GraphicsObjectManager::privInstance();
	assert(pman);
	PCSNode *pRootNode = pman->pRootTree->GetRoot();

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	GraphicsObject *pShader = nullptr, *pResult = nullptr;
	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		pShader = (GraphicsObject*)pNode;
		if (pShader->name  == inName)
		{
			pResult = pShader;
			break;
		}
		pNode = pForwardIter.Next();
	}
	return  pResult;
}

void GraphicsObjectManager::Create()
{
	privCreate();
}

void GraphicsObjectManager::LoadAllGraphicsObject()
{
	GraphicsObject_Null *pNullGraphObject = new GraphicsObject_Null(ModelManager::Find(Model::Name::Null_Object), ShaderObjectManager::Find(ShaderObject::NULL_SHADER));
	GraphicsObjectManager::Add(pNullGraphObject);

	Vect color(1.5f, 1.5f, 1.5f);
	Vect pos(1, 1, 1);

	assert(pNullGraphObject);
	GraphicsObject *pGraphicObject;

	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::SPACE_FRIGATE), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE),Texture::Name::SPACE_FRIGATE, color, pos, GraphicsObject::Name::SPACE_FRIGATE_POINTLIGHT);
	GraphicsObjectManager::Add(pGraphicObject);

	/*pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::ASTROBOY), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::ASTROBOY, color, pos, GraphicsObject::Name::ASTROBOY_POINTLIGHT);
	GraphicsObjectManager::Add(pGraphicObject);
	pGraphicObject->GetModel()->setIsCWW(true);*/

	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::WARBEAR), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::WARBEAR, color, pos, GraphicsObject::Name::WARBEAR_POINTLIGHT);
	GraphicsObjectManager::Add(pGraphicObject);
	pGraphicObject->GetModel()->setIsCWW(true);

	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::BUGGY), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::BUGGY, color, pos, GraphicsObject::Name::BUGGY_POINTLIGHT);
	GraphicsObjectManager::Add(pGraphicObject);

	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::GETHWARRIOR), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::GETHWARRIOR, color, pos, GraphicsObject::Name::GETH_WARRIOR);
	GraphicsObjectManager::Add(pGraphicObject);

	//Collective set
	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::SPACE_FRIGATE), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::SPACE_FRIGATE, color, pos, GraphicsObject::Name::SPACE_FRIGATE_POINTLIGHT2);
	GraphicsObjectManager::Add(pGraphicObject);

	/*pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::ASTROBOY), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::ASTROBOY, color, pos, GraphicsObject::Name::ASTROBOY_POINTLIGHT2);
	GraphicsObjectManager::Add(pGraphicObject);
	pGraphicObject->GetModel()->setIsCWW(true);*/

	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::WARBEAR), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::WARBEAR, color, pos, GraphicsObject::Name::WARBEAR_POINTLIGHT2);
	GraphicsObjectManager::Add(pGraphicObject);
	pGraphicObject->GetModel()->setIsCWW(true);

	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::WARBEAR), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::WARBEAR, color, pos, GraphicsObject::Name::WARBEAR_POINTLIGHT3);
	GraphicsObjectManager::Add(pGraphicObject);
	pGraphicObject->GetModel()->setIsCWW(true);

	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::WARBEAR), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::POLARBEAR, color, pos, GraphicsObject::Name::WARBEAR_POINTLIGHT4);
	GraphicsObjectManager::Add(pGraphicObject);
	pGraphicObject->GetModel()->setIsCWW(true);

	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::BUGGY), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::BUGGY, color, pos, GraphicsObject::Name::BUGGY_POINTLIGHT2);
	GraphicsObjectManager::Add(pGraphicObject);

	pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::GETHWARRIOR), ShaderObjectManager::Find(ShaderObject::Name::POINTLIGHT_TEXTURE), Texture::Name::GETHWARRIOR, color, pos, GraphicsObject::Name::GETH_WARRIOR2);
	GraphicsObjectManager::Add(pGraphicObject);


	//	CUBE_NULL,
	//	CUBE_SIMPLECOLOR,
	//pGraphicObject = new GraphicsObject_SimpleColor(ModelManager::Find(Model::Cube), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::CUBE_SIMPLECOLOR);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	CUBE_CONSTCOLOR,
	//pGraphicObject = new GraphicsObject_ConstColor(ModelManager::Find(Model::Cube), ShaderObjectManager::Find(ShaderObject::CONST_COLOR), color, pos, GraphicsObject::Name::CUBE_CONSTCOLOR);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	CUBE_WIREFRAME,
	//pGraphicObject = new GraphicsObject_WireFrame(ModelManager::Find(Model::Cube), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::CUBE_WIREFRAME);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	CUBE_TEXTURE_Duck,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::SPACE_FRIGATE, GraphicsObject::Name::CUBE_TEXTURE_Duck);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	CUBE_TEXTURE_Brick,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::SPACE_FRIGATE, GraphicsObject::Name::CUBE_TEXTURE_Brick);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	CUBE_TEXTURE_stones,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::STONES, GraphicsObject::Name::CUBE_TEXTURE_stones);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	CUBE_POINTLIGHT_duck,
	// pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::DUCKWEED, color, pos, GraphicsObject::Name::CUBE_POINTLIGHT_duck);
	//GraphicsObjectManager::Add(pGraphicObject);
	//	CUBE_POINTLIGHT_stones,

	
	pGraphicObject = new GraphicsObject_WireframeConstantColor(ModelManager::Find(Model::Name::SPHERE), ShaderObjectManager::Find(ShaderObject::SINGLECOLOR_WIREFRAME), color, GraphicsObject::Name::SPHERE_WIREFRAME);
	GraphicsObjectManager::Add(pGraphicObject);
	pGraphicObject = new GraphicsObject_WireframeConstantColor(ModelManager::Find(Model::Name::CameraModel), ShaderObjectManager::Find(ShaderObject::SINGLECOLOR_WIREFRAME), color, GraphicsObject::Name::CAMERAMODEL_WIREFRAME);
	GraphicsObjectManager::Add(pGraphicObject);

	//	CUBE_POINTLIGHT_Brick,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::RED_BRICK, color, pos, GraphicsObject::Name::CUBE_POINTLIGHT_Brick);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	CUBE_TOON,
	//pGraphicObject = new GraphicsObject_ToonShader(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::TOON_SHADER), GraphicsObject::Name::CUBE_TOON);
	//GraphicsObjectManager::Add(pGraphicObject);

	//
	//
	//	PYRAMID_NULL,
	////	PYRAMID_SIMPLECOLOR,
	//pGraphicObject = new GraphicsObject_SimpleColor(ModelManager::Find(Model::Pyramid), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::PYRAMID_SIMPLECOLOR);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	PYRAMID_CONSTCOLOR,
	//pGraphicObject = new GraphicsObject_ConstColor(ModelManager::Find(Model::Pyramid), ShaderObjectManager::Find(ShaderObject::CONST_COLOR), color, pos, GraphicsObject::Name::PYRAMID_CONSTCOLOR);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	PYRAMID_WIREFRAME,
	//pGraphicObject = new GraphicsObject_WireFrame(ModelManager::Find(Model::Pyramid), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::PYRAMID_WIREFRAME);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	PYRAMID_TEXTURE_Duck,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Pyramid), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::DUCKWEED, GraphicsObject::Name::PYRAMID_TEXTURE_Duck);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	PYRAMID_TEXTURE_Brick,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Pyramid), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::RED_BRICK, GraphicsObject::Name::PYRAMID_TEXTURE_Brick);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	PYRAMID_TEXTURE_stones,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Pyramid), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::STONES, GraphicsObject::Name::PYRAMID_TEXTURE_stones);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	PYRAMID_POINTLIGHT_duck,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::Pyramid), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::DUCKWEED, color, pos, GraphicsObject::Name::PYRAMID_POINTLIGHT_duck);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	PYRAMID_POINTLIGHT_stones,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::Pyramid), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::STONES, color, pos, GraphicsObject::Name::PYRAMID_POINTLIGHT_stones);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	PYRAMID_POINTLIGHT_Brick,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::Pyramid), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::RED_BRICK, color, pos, GraphicsObject::Name::PYRAMID_POINTLIGHT_Brick);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	PYRAMID_TOON,
	//pGraphicObject = new GraphicsObject_ToonShader(ModelManager::Find(Model::Name::Pyramid), ShaderObjectManager::Find(ShaderObject::TOON_SHADER), GraphicsObject::Name::PYRAMID_TOON);
	//GraphicsObjectManager::Add(pGraphicObject);
	////
	////	DIAMOND_NULL,
	////	DIAMOND_SIMPLECOLOR,
	//pGraphicObject = new GraphicsObject_SimpleColor(ModelManager::Find(Model::Diamond), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::DIAMOND_SIMPLECOLOR);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	DIAMOND_CONSTCOLOR,
	//pGraphicObject = new GraphicsObject_ConstColor(ModelManager::Find(Model::Diamond), ShaderObjectManager::Find(ShaderObject::CONST_COLOR), color, pos, GraphicsObject::Name::DIAMOND_CONSTCOLOR);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	DIAMOND_WIREFRAME,
	//pGraphicObject = new GraphicsObject_WireFrame(ModelManager::Find(Model::Diamond), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::DIAMOND_WIREFRAME);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	DIAMOND_TEXTURE_Duck,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Diamond), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::DUCKWEED, GraphicsObject::Name::DIAMOND_TEXTURE_Duck);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	DIAMOND_TEXTURE_Brick,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Diamond), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::STONES, GraphicsObject::Name::DIAMOND_TEXTURE_stones);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	DIAMOND_TEXTURE_stones,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Diamond), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::RED_BRICK, GraphicsObject::Name::DIAMOND_TEXTURE_Brick);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	DIAMOND_POINTLIGHT_duck,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::Diamond), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::DUCKWEED, color, pos, GraphicsObject::Name::DIAMOND_POINTLIGHT_duck);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	DIAMOND_POINTLIGHT_stones,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::Diamond), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::STONES, color, pos, GraphicsObject::Name::DIAMOND_POINTLIGHT_stones);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	DIAMOND_POINTLIGHT_Brick,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::Diamond), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::RED_BRICK, color, pos, GraphicsObject::Name::DIAMOND_POINTLIGHT_Brick);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	DIAMOND_TOON,
	//pGraphicObject = new GraphicsObject_ToonShader(ModelManager::Find(Model::Name::Diamond), ShaderObjectManager::Find(ShaderObject::TOON_SHADER), GraphicsObject::Name::DIAMOND_TOON);
	//GraphicsObjectManager::Add(pGraphicObject);
	////
	////	LOG_NULL,
	////	LOG_SIMPLECOLOR,
	//pGraphicObject = new GraphicsObject_SimpleColor(ModelManager::Find(Model::LOG), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::LOG_SIMPLECOLOR);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	LOG_CONSTCOLOR,
	//pGraphicObject = new GraphicsObject_ConstColor(ModelManager::Find(Model::LOG), ShaderObjectManager::Find(ShaderObject::CONST_COLOR), color, pos, GraphicsObject::Name::LOG_CONSTCOLOR);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	LOG_WIREFRAME,
	//pGraphicObject = new GraphicsObject_WireFrame(ModelManager::Find(Model::LOG), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::LOG_WIREFRAME);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	LOG_TEXTURE_Duck,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::LOG), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::DUCKWEED, GraphicsObject::Name::LOG_TEXTURE_Duck);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	LOG_TEXTURE_Brick,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::LOG), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::STONES, GraphicsObject::Name::LOG_TEXTURE_stones);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	LOG_TEXTURE_stones,
	//pGraphicObject = new GraphicsObject_Texture(ModelManager::Find(Model::Name::LOG), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::RED_BRICK, GraphicsObject::Name::LOG_TEXTURE_Brick);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	LOG_POINTLIGHT_duck,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::LOG), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::DUCKWEED, color, pos, GraphicsObject::Name::LOG_POINTLIGHT_duck);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	LOG_POINTLIGHT_stones,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::LOG), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::STONES, color, pos, GraphicsObject::Name::LOG_POINTLIGHT_stones);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	LOG_POINTLIGHT_Brick,
	//pGraphicObject = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::LOG), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::RED_BRICK, color, pos, GraphicsObject::Name::LOG_POINTLIGHT_Brick);
	//GraphicsObjectManager::Add(pGraphicObject);
	////	LOG_TOON,
	//pGraphicObject = new GraphicsObject_ToonShader(ModelManager::Find(Model::Name::LOG), ShaderObjectManager::Find(ShaderObject::TOON_SHADER), GraphicsObject::Name::LOG_TOON);
	//GraphicsObjectManager::Add(pGraphicObject);

	GraphicsObject_Skybox *pSkybox = new GraphicsObject_Skybox(ModelManager::Find(Model::Name::SKYBOX), ShaderObjectManager::Find(ShaderObject::SKYBOX), Texture::Name::SKYBOX_TEXTURE, GraphicsObject::SKYBOX_TEXTURE);
	GraphicsObjectManager::Add(pSkybox);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*GraphicsObject_SimpleColor *pGraphicsObject_SimpleColor = new GraphicsObject_SimpleColor(ModelManager::Find(Model::Name::Pyramid), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::PYRAMID_SIMPLECOLOR);
	GraphicsObjectManager::Add(pGraphicsObject_SimpleColor);
	assert(pGraphicsObject_SimpleColor);

	GraphicsObject_WireFrame *pGraphicsObject_WireFrame = new GraphicsObject_WireFrame(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::Simple_Color), GraphicsObject::Name::CUBE_WIREFRAME);
	GraphicsObjectManager::Add(pGraphicsObject_WireFrame);
	assert(pGraphicsObject_WireFrame);

	GraphicsObject_Texture *pGraphicsObject_Texture = new GraphicsObject_Texture(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::Texture), Texture::Name::SKYBOX_TEXTURE, GraphicsObject::Name::CUBE_TEXTURE);
	GraphicsObjectManager::Add(pGraphicsObject_Texture);
	assert(pGraphicsObject_Texture);

	
 	GraphicsObject_PointLight *pGraphicsObject_PointLight = new GraphicsObject_PointLight(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::DUCKWEED, color, pos,GraphicsObject::Name::CUBE_POINTLIGHT);
	GraphicsObjectManager::Add(pGraphicsObject_PointLight);

	color.set(1.50f, 1.25f, 3.0f);
	GraphicsObject_ConstColor *pGraphicsObject_ConstColor = new GraphicsObject_ConstColor(ModelManager::Find(Model::Name::Pyramid), ShaderObjectManager::Find(ShaderObject::CONST_COLOR), color, pos, GraphicsObject::Name::PYRAMID_CONSTCOLOR);
	GraphicsObjectManager::Add(pGraphicsObject_ConstColor);

	color.set(1.50f, 1.25f, 3.0f);
	pGraphicsObject_ConstColor = new GraphicsObject_ConstColor(ModelManager::Find(Model::Name::Diamond), ShaderObjectManager::Find(ShaderObject::CONST_COLOR), color, pos, GraphicsObject::Name::DIAMOND_CONSTCOLOR);
	GraphicsObjectManager::Add(pGraphicsObject_ConstColor);


	GraphicsObject_Skybox *pSkybox = new GraphicsObject_Skybox(ModelManager::Find(Model::Name::SKYBOX), ShaderObjectManager::Find(ShaderObject::SKYBOX), Texture::Name::SKYBOX_TEXTURE, GraphicsObject::SKYBOX_TEXTURE);
	GraphicsObjectManager::Add(pSkybox);

	GraphicsObject_ToonShader *ptooncube = new GraphicsObject_ToonShader(ModelManager::Find(Model::Name::Cube), ShaderObjectManager::Find(ShaderObject::TOON_SHADER), GraphicsObject::Name::CUBE_TOON);
	GraphicsObjectManager::Add(ptooncube);
*/

}

GraphicsObjectManager::GraphicsObjectManager()
{
	this->pRootTree = new PCSTree();

	assert(pRootTree != nullptr);
}

GraphicsObjectManager * GraphicsObjectManager::privInstance()
{
	return pGraphicsObjectManager;
}

void GraphicsObjectManager::privCreate()
{
	if (GraphicsObjectManager::pGraphicsObjectManager == nullptr)
	{
		GraphicsObjectManager::pGraphicsObjectManager = new GraphicsObjectManager();

		assert(pGraphicsObjectManager);
	}
}
