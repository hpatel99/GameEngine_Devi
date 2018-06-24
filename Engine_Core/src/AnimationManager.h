#ifndef _ANIMATION_MANAGER
#define _ANIMATION_MANAGER
#include "PCSTree.h"
#include "Animation.h"

class AnimationManager
{
public:

	static void Create();
	 static void Add(Animation *inode_node  );
	 static Animation* Find(Animation::Name inName_);
	static void Update();
	static void IncreaseSpeed();

	~AnimationManager();
private:
	AnimationManager();
	static AnimationManager *privInstance();
	static AnimationManager *pAnimationManager;
	static void privCreate();
	Animation *pHead;
};
#endif

