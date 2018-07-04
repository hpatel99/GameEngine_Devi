#ifndef SKELETON_H
#define SKELETON_H
#include "FrameBucket.h"
#include "GameObject_Anim.h"
#include "GameObjectRigid.h"
#include "ShaderBufferObject.h"
#define BONE_WIDTH 8.0f

class Skeleton : public PCSNode
{
public:
	enum class Name
	{
		TEDDY_SKELETON_WALK,
		TEDDY_SKELETON_IDLE,
		HUMANOID_SKELETON_PUNCH_UNCOMPRESSED,
		HUMANOID_SKELETON_PUNCH_COMPRESSED,

		HUMANOID_SKELETON_SHOT,
		NOT_INITIALZED
	};


	Skeleton(int num,Skeleton::Name inname);
	~Skeleton();
	void LoadInverse(Matrix *fileName);
	void SetBonePose(GameObject* node);
	void SetAnimationPose(GameObject*);
	void Update();
	int getBonesNum();

	

	//data members 
	int numbones;
	Bone *pResult;			//array of bones result used to animate
	Matrix *pPoseInverse;
	Matrix *pWorldOfBones;
	GameObjectAnim *pRoot;	//Root of the bones 
	GameObjectRigid *pRigid;
	Name name;
	ShaderBufferObject *pHeirarchyssbo;
	ShaderBufferObject *pInversessbo;
	int maxDepth;
	Skeleton* pNext;
	Skeleton* pPrev;
};


#endif

