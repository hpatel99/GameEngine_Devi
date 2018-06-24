#include "CameraNode.h"
#include "CameraManager.h"

CameraNode::CameraNode(Camera * pInCamera)
	:PCSNode()
{
	this->pCamera = pInCamera;
	this->ID = CameraManger::idgenerator;
	CameraManger::idgenerator++;
}

//CameraNode* CameraNode::GetNextCamera()
//{
//	if(this->GetNextSibling()!= nullptr)
//	{
//		return (CameraNode*)this->GetNextSibling();
//	}
//	else
//	{
//		return (CameraNode*)this->GetParent()->GetChild();
//	}
//}
