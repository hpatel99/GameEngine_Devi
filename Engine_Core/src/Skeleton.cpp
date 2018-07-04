#include "Skeleton.h"
#include "PCSTreeForwardIterator.h"
#include "GraphicsObject_PointLight.h"
#include "PCSTree.h"
#include "GameObjectManager.h"
#include "GraphicsObject_Null.h"
#include "ModelManager.h"
#include "ShaderObjectManager.h"
#include "GameObjectRigid.h"
#include "Matrix.h"


Skeleton::Skeleton(int num, Skeleton::Name inname)
{
	this->numbones = num;
	this->name =inname;
	
	//ssbo initialzed
	this->pHeirarchyssbo = new ShaderBufferObject();
	this->pInversessbo = new ShaderBufferObject();
	this->pResult = new Bone[(unsigned)num]();
	this->pPoseInverse = new Matrix[100]();
	this->pWorldOfBones = new Matrix[100]();
	this->pRigid = nullptr;
	this->pRoot = nullptr;
}

Skeleton::~Skeleton()
{
	delete[] this->pResult;
	delete[] this->pPoseInverse;
	delete[] this->pWorldOfBones;
}

void Skeleton::LoadInverse(Matrix * fileName)
{
	//TODO own a copy this inverse are not owned by you...(Who will call delte?)
	this->pPoseInverse = fileName;
}

void Skeleton::SetBonePose(GameObject *node)
{
	// Now get the world matrices
	// getting the parent from current node
	GameObjectAnim *childNode = (GameObjectAnim *)node;
	//GameObjectAnim *parentNode = (GameObjectAnim *)node->GetParent();

	GameObjectAnim *parentNode;
	if (node->GetParent()->GetParent()->GetParent() != 0)
		parentNode = (GameObjectAnim *)node->GetParent();
	else
		parentNode = 0;

	if (parentNode != 0 && childNode != 0)
	{
		// starting point
		Vect start(0.0f, 0.0f, 0.0f);

		//  At this point, Find the two bones initial positions in world space
		//  Now get the length and directions

		Vect ptA = start * *parentNode->getWorld();
		Vect ptB = start * *childNode->getWorld();

		// direction between the anchor points of the respective bones
		Vect dir = (ptA - ptB);

		// length of the bone 0
		float mag = dir.mag();

		Vect Up(0, 1, 0);
		Up = Up * *parentNode->getWorld();

		Matrix S(SCALE, BONE_WIDTH, BONE_WIDTH, mag);
		Quat Q(ROT_ORIENT, dir.getNorm(), Up);
		Matrix T(TRANS, ptB);

		Matrix BoneOrient = S * Q * T;

		childNode->SetBoneOrientation(BoneOrient);
	}
}

void Skeleton::SetAnimationPose(GameObject *proot)
{
	PCSTreeForwardIterator pIter(proot);
	PCSNode *pNode = pIter.First();
	GameObject *pGameObj = 0;

	// walks the anim node does the pose for everything that
	while (pNode != 0)
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;
		SetBonePose(pGameObj);

		pNode = pIter.Next();
	}
}

void Skeleton::Update()
{
	SetAnimationPose(pRoot);

}

int Skeleton::getBonesNum()
{
	return this->numbones;
}


