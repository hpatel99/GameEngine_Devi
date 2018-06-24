#include "CameraManager.h"
#include "GameObjectManager.h"
CameraManger *CameraManger::pCameraManager = 0;//forward declaration for static
int CameraManger::idgenerator;
void CameraManger::Add(Camera * inCamera)
{
	assert(inCamera != nullptr);
	CameraManger *pman = CameraManger::privInstance();
	PCSNode *pRoot = pman->pRootTree->GetRoot();
	CameraNode *pNode = new CameraNode(inCamera);
	pman->pRootTree->Insert(pNode, pRoot);
	pman->pActiveNode = pNode;
	pRoot = pman->pRootTree->GetRoot();
	/*pman->it = new PCSTreeForwardIterator(pman->pRootTree->GetRoot());
*/
}

void CameraManger::Create()
{
	privCreate();
}

void CameraManger::Update()
{
	CameraManger::GetActive()->updateCamera();
	CameraManger::pCameraManager->pModelOfFrustrum->update();
}

Camera * CameraManger::GetActive()
{
	CameraManger *pman = CameraManger::privInstance();
	CameraNode *pNode = (CameraNode*)pman->pActiveNode;
	
	return pNode->pCamera;
}

void CameraManger::SetActive(CameraNode *inCamera)
{
	CameraManger *pman = CameraManger::privInstance();
	pman->pActiveNode = inCamera;
}

void CameraManger::Changeto(int id)
{
	CameraManger *pman = CameraManger::privInstance();

	PCSTreeForwardIterator *it = new PCSTreeForwardIterator(pman->pRootTree->GetRoot());

	while (!it->IsDone())
	{
		CameraNode *node = (CameraNode*)it->CurrentItem();
		if (node->ID == id)
		{
			pman->pActiveNode = node;
			break;
		}
		it->Next();
	}
/*if(pman->pActiveNode->GetChild() == nullptr)
	{
		pman->pActiveNode = pman->pActiveNode->GetParent();
	}
	else
	{
		pman->pActiveNode = pman->pActiveNode->GetChild();
	}*/
	/*if(pman->it->IsDone())
	{
		pman->it->First();
		
	}
	else
	{
		pman->it->Next();

	}
	pman->pActiveNode = pman->it->CurrentItem();*/

}

bool CameraManger::IsInFrustrum(Vect &inpos,float inrad)
{
	bool result = pCameraManager->pFrustrumRender->isItInYet(inpos, inrad/2);



	return result;
}

CameraManger::CameraManger()
{
	this->pRootTree = new PCSTree;
	this->pFrustrumRender = nullptr;
	this->pModelOfFrustrum = nullptr;
	this->idgenerator = 1;
	assert(pRootTree);
}

CameraManger * CameraManger::privInstance()
{
	return pCameraManager;
}

void CameraManger::privCreate()
{
	if(CameraManger::pCameraManager == nullptr)
	{
		CameraManger::pCameraManager = new CameraManger();
		assert(CameraManger::pCameraManager);
	}
}
