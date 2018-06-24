#ifndef _CLIP
#define _CLIP
#include "FrameBucket.h"

class Clip
{
public :
	enum class Name
	{
		TEDDY_WALK,
		TEDDY_IDLE,
		NOT_INITIALIZE,
		HUMANOID_SHOT,
		HUMANOID_PUNCH
	};

	Clip(Clip::Name inname);

	~Clip();
	
	

	//data member
	
	Clip::Name name;			//name of clip
	Clip *PNext;
	Clip *pPrev;
	Frame_Bucket *PheadBucket;	//Head of frame bucket
	
	
	


};

#endif
