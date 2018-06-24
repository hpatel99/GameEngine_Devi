#include "ModelManager.h"
#include "PCSTreeForwardIterator.h"
#include "NullModel.h"
#include "CubeModel.h"
#include "PyramidModel.h"
#include "SkyBox.h"
#include "Diamond.h"
#include "Log.h"
#include "Sphere.h"
#include "CameraModel.h"

#include "CameraManager.h"

ModelManager *ModelManager::pModelManager = 0;

void ModelManager::Add(PCSNode * inNode)
{
	assert(inNode != nullptr);
	ModelManager *pman = ModelManager::privInstance();
	PCSNode *pRoot = pman->pRootTree->GetRoot();
	pman->pRootTree->Insert(inNode, pRoot);
}

Model * ModelManager::Find(Model::Name inname)
{
	ModelManager *pman = ModelManager::privInstance();
	assert(pman);
	PCSNode *pRootNode = pman->pRootTree->GetRoot();

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	Model *pModel = nullptr,*pResult = nullptr;
	while(!pForwardIter.IsDone())
	{
		assert(pNode);
		pModel = (Model*)pNode;
		if(pModel->name == inname)
		{
			pResult = pModel;
			break;
		}
		pNode = pForwardIter.Next();
	}
	return  pResult;


}

void ModelManager::Create()
{
	privCreate();
}

void ModelManager::LoadAllModels()
{
	CubeModel *pcubemodel = new CubeModel("cubeModel.azul");
	assert(pcubemodel);
	ModelManager::Add(pcubemodel);

	PyramidModel *pPyramidModel = new PyramidModel("PyramidModel.azul");
	assert(pPyramidModel);
	ModelManager::Add(pPyramidModel);

	SkyBox *pSkybox = new SkyBox("Skybox.azul");
	ModelManager::Add(pSkybox);

	DiamondModel *pDiamondModel = new DiamondModel("Diamond.azul");
	assert(pDiamondModel);
	ModelManager::Add(pDiamondModel);

	LogModel *pLogModel = new LogModel("Log.azul");
	assert(pLogModel);
	ModelManager::Add(pLogModel);

	SphereModel *PSphereModel = new SphereModel("Sphere.Azul");
	assert(PSphereModel);
	ModelManager::Add(PSphereModel);

	CameraModel *p_camera_model = new CameraModel("CamModel.Azul");
	assert(p_camera_model);
	ModelManager::Add(p_camera_model);
	CameraManger::pCameraManager->pModelOfFrustrum = p_camera_model;

	//SpaceModel *p_space_model = new	SpaceModel("Space_Frigate.devi");
	//assert(p_space_model);
	//ModelManager::Add(p_space_model);

}

ModelManager::ModelManager()
{
	this->pRootTree = new PCSTree();

	NullModel *pNULL = new NullModel("NullModel.Azul");
	pRootTree->Insert(pNULL, nullptr);
	assert(pRootTree != nullptr);
}

ModelManager * ModelManager::privInstance()
{
	return pModelManager;
}

void ModelManager::privCreate()
{
	if (ModelManager::pModelManager == nullptr)
	{
		ModelManager::pModelManager = new ModelManager();
		assert(pModelManager);
	}
}
