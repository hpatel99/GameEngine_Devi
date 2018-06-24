#ifndef _ANIMATION_H
#define  _ANIMATION_H
#include "Clip.h"
#include "PCSNode.h"
#include "Skeleton.h"
#include "ShaderBufferObject.h"


class  Animation : public PCSNode
{
public :
	enum class Name
	{
		TEDDY_ANIMATION_IDLE, 
		TEDDY_ANIMATION_WALK,
		NOT_INITIALIZED,
		HUMANOID_ANIMATION_SHOT,
		HUMANOID_ANIMATION_PUNCH,
	};


	Animation() = delete;
	Animation(Skeleton::Name inSkelName_,Animation::Name inName_,bool Gpuanimation = false);
	~Animation();
	void ProcessAnimation();
	void PushDataToSkeleton();
	void SetSpeed(float inspeed);
	float GetSpeed(void);
	void Update();
	

	void increaseSpeed();
	void decreaseSpeed();
	void AddClip(Clip *inClip);
	void Remove(Clip *inClip);
	Clip* Find(Clip::Name inname);
	void FindMaxTime(Time &tMax);

	//Data
	Clip *pClipHead;
	Clip *pActiveClip;
	Animation *pNext;
	Animation *pPrev;

	Skeleton *pSkeleton;
	float speed;
	//ssbo for interpolation
	
	ShaderBufferObject *pFrameC_ssbo;
	ShaderBufferObject *pFrameD_ssbo;
	ShaderBufferObject *pFrameA_ssbo;//in
	ShaderBufferObject *pFrameB_ssbo;//in
	ShaderBufferObject *plocalmatrix_ssbo;

	//ssbo for loacl to world
	ShaderBufferObject *pBit_ssbo;//output is saved here

	const static unsigned int LOCAL_COMPUTE_THREAD_COUNT = 20;
	Name name;
	bool gpuAnimation;
	char pad[3];
	Time tcurrent;
private:
	void privProcessGPUanim(Frame_Bucket *pA, Frame_Bucket*pB, float t_);
	void privProcessCPUanim(Frame_Bucket *pA, Frame_Bucket*pB, float t_);
	
};


#endif

