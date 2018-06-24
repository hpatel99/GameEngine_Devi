#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

#include "PCSNode.h"
#include "Camera.h"

class CameraNode : public PCSNode
{
public:
	
	CameraNode(Camera *pInCamera);
	
private:
	
	CameraNode() =delete;
	//data memebere
public:
	Camera *pCamera;
	int ID;
};
#endif
