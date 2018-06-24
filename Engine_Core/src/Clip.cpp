#include "Clip.h"

Clip::Clip(Clip::Name inname)
{




	this->pPrev = nullptr;
	this->PNext = nullptr;
	this->PheadBucket = nullptr;
	this->name = inname;
	//SetAnimationData();

}

Clip::~Clip()
{
	this->pPrev = nullptr;
	this->PNext = nullptr;
	this->PheadBucket = nullptr;
}




