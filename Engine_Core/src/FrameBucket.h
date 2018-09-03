#ifndef FRAME_BUCKET
#define FRAME_BUCKET

#include "Timer.h"
#include "Vect.h"
#include "Quat.h"

struct Bone : public Align16
{
   Vect  T;
   Quat  Q;
   Vect  S;
};

struct Frame_Bucket
{
	
	
	Time		  KeyTime;
	Bone		  *pBone;
	Frame_Bucket *prevBucket;
	Frame_Bucket *nextBucket;
	char		  pad[4];

	Frame_Bucket()				//constructor
	{
		this->nextBucket = nullptr;
		this->prevBucket = nullptr;
		this->pBone = nullptr;
		this->KeyTime = Time(Time::ZERO);
	}
	~Frame_Bucket()
	{
		this->nextBucket = nullptr;
		this->prevBucket = nullptr;
		delete[] pBone;
	}
};


#endif