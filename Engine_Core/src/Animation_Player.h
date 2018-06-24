#pragma once
#include "Clip.h"

class Animation_Player
{
public:
	
	~Animation_Player();
	Animation_Player(const Animation_Player&) = delete;
	Animation_Player &operator = (const Animation_Player&) = delete;

	static void Create();
	static Clip* GetCurrentClip();
	static void SetClip(Clip *inclip);
	
	//HACK adding all to public need refactor
	//Data member
	static void Update();
	
	static Time DeltaTime;	// delta t
	static Time tCurrent;	// delta t
	
	 Clip *pCurrentClip;
	 static float Diff;

private:
	Animation_Player();
	static Animation_Player *privInstance();
	static Animation_Player *pAnimation_Player;
	static void privCreate();
};

