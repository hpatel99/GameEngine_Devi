#include "Clip.h"

Clip::Clip(Clip::Name inname)
{
	this->pPrev = nullptr;
	this->PNext = nullptr;
	this->PheadBucket = nullptr;
	this->name = inname;
}

Clip::~Clip()
{
	this->pPrev = nullptr;
	this->PNext = nullptr;
	Frame_Bucket *pConductor = this->PheadBucket;
	while (pConductor != nullptr)
	{
		Frame_Bucket *toBeDeleted = pConductor;
		pConductor = pConductor->nextBucket;
		delete toBeDeleted;

		
	}

}




