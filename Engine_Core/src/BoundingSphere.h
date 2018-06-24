#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "Vect.h"

struct Sphere: public Align16
{
	Vect cntr;
	float rad;
	float pad[3];  // love and hate this new compiler
};

void RitterSphere(Sphere &s, Vect *pt, int numPts);
#endif
