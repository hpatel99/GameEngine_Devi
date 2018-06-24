#include "SkeletonManager.h"
#include "PCSTreeForwardIterator.h"
#include "Skeleton.h"

SkeletonManager* SkeletonManager::pSkeletonManger;

SkeletonManager::SkeletonManager()
{
	this->pHead = nullptr;
	
}

SkeletonManager * SkeletonManager::privInstance()
{
	return pSkeletonManger;
}

void SkeletonManager::privCreate()
{
	if(pSkeletonManger == nullptr)
	{
		pSkeletonManger = new SkeletonManager();
	}
}


void SkeletonManager::Create()
{
	privCreate();
}

void SkeletonManager::Add(Skeleton * inNode)
{
	assert(inNode != nullptr);
	
		SkeletonManager *pMan = SkeletonManager::privInstance();
		assert(inNode != nullptr);
		if (pMan->pHead == 0)
		{
			pMan->pHead = inNode;
			inNode->pNext = nullptr;
			inNode->pPrev = nullptr;
		}
		else
		{
			inNode->pNext = pMan->pHead;
			pMan->pHead->pPrev = inNode;
			pMan->pHead = inNode;

		}
}

void SkeletonManager::Update()
{
	SkeletonManager *pskelman = SkeletonManager::privInstance();
	assert(pskelman);
	Skeleton *PSkel = pskelman->pHead;
	while (PSkel != nullptr)
	{
		PSkel->Update();
		PSkel = PSkel->pNext;
	}

}

Skeleton* SkeletonManager::Find(Skeleton::Name inname)
{
	SkeletonManager *pskelman = SkeletonManager::privInstance();
	Skeleton * pconductor = pskelman->pHead;
	while(pconductor!= nullptr)
	{
		if(pconductor->name == inname)
		{
			return pconductor;
		}
		pconductor = pconductor->pNext;
	}
	assert(false);	//should not be here at first place
	return nullptr;

}

SkeletonManager::~SkeletonManager()
{
}
