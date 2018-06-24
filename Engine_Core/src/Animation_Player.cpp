#include "Animation_Player.h"


Animation_Player *Animation_Player::pAnimation_Player;
Time Animation_Player::tCurrent;
Time Animation_Player::DeltaTime;
float Animation_Player::Diff;


Animation_Player::Animation_Player()
{
	this->DeltaTime =  Time(Time::ZERO);
	this->pCurrentClip = nullptr;
	this->Diff = 0.0f;

}


Animation_Player::~Animation_Player()
{
}

void Animation_Player::Create()
{
		privInstance()->privCreate();
}

Clip * Animation_Player::GetCurrentClip()
{
	return pAnimation_Player->pCurrentClip;
}

void Animation_Player::SetClip(Clip * inclip)
{
	privInstance()->pCurrentClip = inclip;
}

void Animation_Player::Update()
{
	Time deltaTime = Animation_Player::Diff * Time(Time::NTSC_30_FRAME);
	
	Time maxTime = privInstance()->pCurrentClip->maxtime;	// get the max time

	tCurrent += deltaTime;


	// protection for time values for looping
	if (tCurrent < Time(Time::ZERO))
	{
		tCurrent = maxTime;
	}
	else if (tCurrent > maxTime)
	{
		tCurrent = Time(Time::ZERO);
	}
	else
	{
		// do nothing
	}

}

Animation_Player * Animation_Player::privInstance()
{
	return pAnimation_Player;
}

void Animation_Player::privCreate()
{
	if(pAnimation_Player == nullptr)
	{
		pAnimation_Player = new Animation_Player();
		assert(pAnimation_Player);
	}
}
