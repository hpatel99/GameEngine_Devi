#ifndef _ANIMATION_MANAGER
#define _ANIMATION_MANAGER
#include "PCSTree.h"
#include "Animation_Player.h"

class AnimationManager
{
public:

	static void Create();
	static void Destroy();

	 static void Add(Animation_Player *inode_node  );
	 static Animation_Player* Find(Animation_Player::Name inName_);
	static void Update();
	static void IncreaseSpeed();

	~AnimationManager();
private:
	AnimationManager();
	static AnimationManager *privInstance();
	static AnimationManager *pAnimationManager;
	static void privCreate();
	Animation_Player *pHead;
};
#endif

