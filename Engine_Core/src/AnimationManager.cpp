#include "AnimationManager.h"
#include "PCSTreeForwardIterator.h"
#include "Animation.h"

AnimationManager *AnimationManager::pAnimationManager;

AnimationManager::AnimationManager()
{
	this->pHead = nullptr;
	
}

AnimationManager * AnimationManager::privInstance()
{
	return pAnimationManager;
}

void AnimationManager::privCreate()
{
	if(pAnimationManager == nullptr)
	{
		pAnimationManager = new AnimationManager();
		assert(pAnimationManager);
	}
}


void AnimationManager::Create()
{
	privCreate();
}

void AnimationManager::Add(Animation * inode_node)
{
	AnimationManager *pMan = AnimationManager::privInstance();

	assert(inode_node != nullptr);
	if (pMan->pHead == 0)
	{
		pMan->pHead = inode_node;
		inode_node->pNext = nullptr;
		inode_node->pPrev = nullptr;
	}
	else
	{
		inode_node->pNext = pMan-> pHead;
		pMan->pHead->pPrev = inode_node;
		pMan->pHead = inode_node;

	}


}

Animation * AnimationManager::Find(Animation::Name inName_)
{
	Animation* pConductor = pAnimationManager->pHead;
	assert(pConductor != nullptr);
	while (pConductor)
	{
		if(pConductor->name == inName_)
		{
			return pConductor;
		}
		pConductor = pConductor->pNext;
		
	}
	assert(FALSE);		// this means there was no result found should not happen
	return nullptr;
}

void AnimationManager::Update()
{
	AnimationManager *pMan = AnimationManager::privInstance();
	assert(pMan);
	Animation *pAnim = pMan->pHead;
	while (pAnim != nullptr)
	{
		pAnim->Update();
		pAnim = pAnim->pNext;

	}

	//animate here
}

void AnimationManager::IncreaseSpeed()
{
	AnimationManager *pMan = AnimationManager::privInstance();
	assert(pMan);
	Animation *pAnim = pMan->pHead;
	while (pAnim != nullptr)
	{
		pAnim->increaseSpeed();
		pAnim = pAnim->pNext;

	}
}

AnimationManager::~AnimationManager()
{

}
