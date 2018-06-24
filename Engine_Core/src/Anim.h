#ifndef ANIM_H
#define ANIM_H

#include "Timer.h"

#include "GameObject.h"

#define NUM_BONES 20

void SetAnimationHierarchy();
void SetAnimationData();
//void SetAnimationPose(GameObject *node);
void SetAnimationPose(GameObject *root, Time tCurr);

void ProcessAnimation(Time tCurr);
void FindMaxTime(Time &tMax);

#endif