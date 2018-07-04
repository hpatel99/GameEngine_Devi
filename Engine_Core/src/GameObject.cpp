#include "MathEngine.h"
#include "GameObject.h"
#include "Game.h"
#include "Model.h"
#include <assert.h>
#include "ShaderObject.h"
#include "GraphicsObjectManager.h"
#include "CameraManager.h"
#include "GraphicsObject_WireframeConstantColor.h"


extern Game *pGame;



Matrix *GameObject::getWorld()
{
	return this->pWorld;
}
GraphicsObject * GameObject::GetGraphicsObject()
{
	return this->pGraphicsObject;
}
GameObject::GameObject(GraphicsObject *pGraphicsObject)
	:pGraphicsObject(pGraphicsObject)
{
	assert(pGraphicsObject != nullptr);
	this->pWorld = new Matrix(IDENTITY);
	
}

void GameObject::draw()
{
	assert(this->pGraphicsObject != nullptr);
	//const Model *pModel = this->pGraphicsObject->GetModel();

	// push to graphics object
	this->pGraphicsObject->SetWorld(*this->pWorld);
	this->pGraphicsObject->Render();

	//if(pModel->IsRenderSphere() )
	//{
	//	//TODO  render sphere 
	//	GraphicsObject_WireframeConstantColor *p_sphere =(GraphicsObject_WireframeConstantColor*) GraphicsObjectManager::Find(GraphicsObject::Name::SPHERE_WIREFRAME);
	//	Matrix Radius(SCALE,Vect(pModel->psphere->rad, pModel->psphere->rad, pModel->psphere->rad));
	//	
	//	Matrix Center(TRANS, pModel->psphere->cntr);
	//	Matrix GOWorld(*this->pWorld);
	//	
	//	
	//	Matrix Result = Radius * Center * GOWorld;
	//	Vect Pos(Result.get(ROW_3));					//getting positiion vector of the object
	//	
	//	if(CameraManger::IsInFrustrum(Pos,pModel->psphere->rad * this->pScale->x()))
	//	{
	//		Vect incolor(1.0f, 0.0f, 0.0f);
	//		p_sphere->setcolor(&incolor);
	//	}
	//	else
	//	{
	//		Vect incolor(1.0f, 1.0f, 1.0f);
	//		p_sphere->setcolor(&incolor);
	//	}
	//	//settign sphere to position and drrawing

	//	p_sphere->SetWorld(Result);
	//	p_sphere->Render();
	//}
}

void GameObject::Process(Time t)
{

	// Goal: update the world matrix
	this->Update(t);


}

void GameObject::setWorld(Matrix * world)
{
	assert(world);
	*this->pWorld = *world;
}

//void GameObject::setPos(const Vect & pos)
//{
//	*this->pTrans = pos;
//}
//
//void GameObject::setScale(const Vect &inScale)
//{
//	*this->pScale = inScale;
//}

//void GameObject::rotate(Rot3AxisType intype,const  float angle1,const float angle2,const  float angle3)
//{
//	switch (intype)
//	{
//	case ROT_XYZ:		//x y z in the order
//		this->rotX = angle1;
//		this->rotY = angle2;
//		this->rotZ = angle3;
//
//		break;
//	default:
//		break;
//	}
//
//	Matrix Scale(SCALE, *this->pScale);
//	Matrix TransA(TRANS, *this->pTrans);
//	Matrix RotX(ROT_X, this->rotX);
//	Matrix RotY(ROT_Y, this->rotY);
//	Matrix RotZ(ROT_Z, this->rotZ);
//	*this->pWorld = Scale * RotX * RotY * RotZ * TransA;
//
//}



GameObject::~GameObject()
{
	delete this->pWorld;
}

void GameObject::Update( Time currentTime )
{	
	UNUSED_VAR(currentTime);

}
