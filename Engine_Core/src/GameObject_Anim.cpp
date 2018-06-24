#include "GameObject_Anim.h"
#include "FrameBucket.h"
#include "AnimationManager.h"

extern Frame_Bucket *pHead;
GameObjectAnim::GameObjectAnim(GraphicsObject * graphicsObject)
	:GameObject(graphicsObject)
{
	assert(graphicsObject != nullptr);
	this->pDof = new Vect(0.0f, 0.0f, 0.0f, 0.0f);
	assert(this->pDof);

	this->pUp = new Vect(0.0f, 1.0f, 0.0f);
	assert(pUp);

	this->pScale = new Vect(1.0f, 1.0f, 1.0f);
	assert(pScale);

	this->pPos = new Vect(0.0f, 0.0f, 0.0f);
	assert(pPos);

	this->pLocal = new Matrix(IDENTITY);
	assert(pLocal);

	this->pBoneOrientation = new Matrix(IDENTITY);
	assert(pBoneOrientation);

	this->indexBoneArray = 0;
}

GameObjectAnim::~GameObjectAnim()
{
	delete this->pDof;
	delete this->pLocal;
	delete this->pScale;
	delete this->pBoneOrientation;
	delete this->pUp;
	delete this->pLocal;

}

void GameObjectAnim::Update(Time )
{
	GameObject *pBoneParent = (GameObject *)this->GetParent();
	assert(pBoneParent != 0);

	Matrix ParentWorld = *pBoneParent->getWorld();

	// REMEMBER this is for Animation and hierachy, you need to handle models differently
	// Get the result bone array, from there make the matrix
	
	Bone *bResult = Pskeleton->pResult;

	Matrix T = Matrix(TRANS, bResult[indexBoneArray].T);
	Matrix S = Matrix(SCALE, bResult[indexBoneArray].S);
	Quat   Q = bResult[indexBoneArray].Q;

	// Isn't awesome that we can multiply Quat with matrices!
	Matrix M = S * Q * T;
	*this->pLocal = M;

	// Goal: update the world matrix
	*this->pWorld = *this->pLocal * ParentWorld;
	//this->SubmitWorld();

}

void GameObjectAnim::Process(Time currentTime)
{
	this->Update(currentTime);
}

void GameObjectAnim::draw()
{
	assert(this->pGraphicsObject != nullptr);
	//const Model *pModel = this->pGraphicsObject->GetModel();

	// push to graphics object
	this->pGraphicsObject->SetWorld(*this->pBoneOrientation);
	// disabling the render so bones would not stick out of model
	//this->pGraphicsObject->Render();

}

void GameObjectAnim::SetIndex(const int val)
{
	this->indexBoneArray = val;
}

void GameObjectAnim::SetBoneOrientation(const Matrix & in_matrix)
{
	this->pBoneOrientation->set(in_matrix);
}

Matrix GameObjectAnim::GetBoneOrientation(void) const
{
	return (*this->pBoneOrientation);
}

void GameObjectAnim::SubmitWorld()
{
	Pskeleton->pWorldOfBones[indexBoneArray] = *this->pWorld;

}
