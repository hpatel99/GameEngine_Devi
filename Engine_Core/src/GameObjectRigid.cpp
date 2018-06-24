#include <assert.h>
#include <math.h>

#include "PCSNode.h"
#include "MathEngine.h"
#include "GameObject.h"
#include "GraphicsObject.h"
#include "Anim.h"
#include "FrameBucket.h"
#include "GameObjectRigid.h"

GameObjectRigid::GameObjectRigid( GraphicsObject  *graphicsObject )
	: GameObject(graphicsObject)
{
	this->pScale = new Vect(1.0f, 1.0f, 1.0f);
	assert(this->pScale);

	this->pPos = new Vect(0.0f,0.0f,0.0f);
	assert(this->pPos);
}

GameObjectRigid::~GameObjectRigid()
{
	delete this->pPos;
	delete this->pScale;
}



Matrix &GameObjectRigid::GetWorld()
{
	return *this->pWorld;
}

void GameObjectRigid::Update( Time  )
{
	Matrix T = Matrix( TRANS, *this->pPos);
	Matrix S = Matrix( SCALE, *this->pScale);
	Matrix R = Matrix(ROT_X, this->rotX)*Matrix(ROT_Y, this->rotY)*Matrix(ROT_Z, this->rotZ);

	Matrix M = S * R * T;

	*this->pWorld = M;
}

void GameObjectRigid::setScale(const Vect & invect)
{
	*this->pScale = invect;
}

void GameObjectRigid::setPos(const Vect & pos)
{
	*this->pPos = pos;
}

void GameObjectRigid::rotate(Rot3AxisType intype,const  float angle1,const float angle2,const  float angle3)
{
	switch (intype)
	{
	case ROT_XYZ:		//x y z in the order
		this->rotX = angle1;
		this->rotY = angle2;
		this->rotZ = angle3;

		break;
	default:
		break;
	}

}