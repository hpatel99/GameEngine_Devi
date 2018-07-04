#include "AnimationManager.h"
#include "PCSTreeForwardIterator.h"
#include "Animation_Player.h"

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

void AnimationManager::Destroy()
{
	AnimationManager *pMan = AnimationManager::privInstance();
	delete pMan;
}

void AnimationManager::Add(Animation_Player * inode_node)
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

Animation_Player * AnimationManager::Find(Animation_Player::Name inName_)
{
	Animation_Player* pConductor = pAnimationManager->pHead;
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
	Animation_Player *pAnim = pMan->pHead;
	while (pAnim != nullptr)
	{
		pAnim->Update();
		pAnim = pAnim->pNext;

	}

	
}

void AnimationManager::IncreaseSpeed()
{
	AnimationManager *pMan = AnimationManager::privInstance();
	assert(pMan);
	Animation_Player *pAnim = pMan->pHead;
	while (pAnim != nullptr)
	{
		pAnim->increaseSpeed();
		pAnim = pAnim->pNext;

	}
}

AnimationManager::~AnimationManager()
{
	AnimationManager *pMan = AnimationManager::privInstance();
	assert(pMan);
	Animation_Player *pAnim = pMan->pHead;
	while(pAnim != nullptr)
	{
		Animation_Player *pToBeDeleted = pAnim;
		pAnim = pAnim->pNext;
		delete pToBeDeleted;
	}
}
