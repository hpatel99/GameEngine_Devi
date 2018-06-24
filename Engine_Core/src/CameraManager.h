#ifndef CAMERA_MANAGER_H
#define CAMERA_MANGER_H

#include "PCSTree.h"
#include "CameraNode.h"
#include "Camera.h"
#include "PCSTreeForwardIterator.h"
#include "CameraModel.h"

class CameraManger
{
public:
	static void Add(Camera *inNode);
	static void Create();
	static void Update();
	static Camera* GetActive();
	static void SetActive(CameraNode *inCamera);
	static void Changeto(int id);
	static bool IsInFrustrum(Vect &inpos,float inrad);


	//Data
public:
	CameraManger();
	static int idgenerator;
	static CameraManger*privInstance();
	static CameraManger *pCameraManager;
	static void privCreate();
	PCSTree *pRootTree;
	PCSNode *pActiveNode;
	Camera* pFrustrumRender;			//camera whose frustrum is rendering 
	CameraModel *pModelOfFrustrum;		// acctual  model of the frustrum
	//PCSTreeForwardIterator *it;
};
#endif

