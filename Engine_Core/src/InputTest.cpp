#include "InputTest.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.H"

#include "Camera.h"
#include "CameraManager.h"
#include "GameObjectManager.h"
#include "GraphicsObjectManager.h"
#include "GraphicsObject_PointLight.h"
#include "AnimationManager.h"
#include "SkeletonManager.h"
#include "Trace.h"
#include "Vect.h"


void KeyboardTest()
{
	Vect pos;						 //for camera stuff
	Vect tar;						 //for camera stuff
	Vect up;						 //for camera stuff
	Vect upNorm;					 //for camera stuff
	Vect forwardNorm;				 //for camera stuff
	Vect rightNorm;					 //for camera stuff
	float movespeed = 0.2f;
	Keyboard *pKey = InputManager::GetKeyboard();
	
	if (pKey->GetKeyState(AZUL_KEY::KEY_1))
	{
		CameraManger::Changeto(1);

	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_2))
	{
		CameraManger::Changeto(2);

	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_3))
	{
		CameraManger::Changeto(3);

	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_4))
	{
		CameraManger::Changeto(4);

	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_5))
	{
		CameraManger::Changeto(5);

	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_6))
	{
		CameraManger::Changeto(6);

	}

	if (pKey->GetKeyState(AZUL_KEY::KEY_P))						//Swapptexture
	{
		GraphicsObject_PointLight *p_graphics_object = (GraphicsObject_PointLight*)GraphicsObjectManager::Find(GraphicsObject::Name::WARBEAR_POINTLIGHT3);
		if(p_graphics_object->textName == Texture::Name::WARBEAR)
		{
			p_graphics_object->textName = Texture::Name::POLARBEAR;
		}
		p_graphics_object = (GraphicsObject_PointLight*)GraphicsObjectManager::Find(GraphicsObject::Name::WARBEAR_POINTLIGHT4);
		if (p_graphics_object->textName == Texture::Name::WARBEAR)
		{
			p_graphics_object->textName = Texture::Name::POLARBEAR;
		}
		

		
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_O))						//Swapptexture
	{
		GraphicsObject_PointLight *p_graphics_object = (GraphicsObject_PointLight*)GraphicsObjectManager::Find(GraphicsObject::Name::WARBEAR_POINTLIGHT3);
		if (p_graphics_object->textName == Texture::Name::POLARBEAR)
		{
			p_graphics_object->textName = Texture::Name::WARBEAR;
		}
		p_graphics_object = (GraphicsObject_PointLight*)GraphicsObjectManager::Find(GraphicsObject::Name::WARBEAR_POINTLIGHT4);
		if (p_graphics_object->textName == Texture::Name::POLARBEAR)
		{
			p_graphics_object->textName = Texture::Name::WARBEAR;
		}

	}

	if (pKey->GetKeyState(AZUL_KEY::KEY_L))						//Swapptexture
	{
		

	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_K))						//Swapptexture
	{
		AnimationManager::IncreaseSpeed();

	}
	//if (pKey->GetKeyState(AZUL_KEY::KEY_2))
	//{
	//	GraphicsObject_Texture *pgraphicObj = (GraphicsObject_Texture*)pGameObj3->GetGraphicsObject();
	//	pgraphicObj->textName = Texture::Name::DUCKWEED;
	//}

	if (pKey->GetKeyState(AZUL_KEY::KEY_A))						//truck
	{
		

		
		CameraManger::GetActive()->MoveLeft(movespeed);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_D))					//truck
	{
		CameraManger::GetActive()->MoveRight(movespeed);
	}
	if(pKey->GetKeyState(AZUL_KEY::KEY_W))				//tilt  //tilt
	{
		CameraManger::GetActive()->MoveForward(movespeed);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_S))					//tilt  //tilt
	{

		CameraManger::GetActive()->MoveBackward(movespeed);
	}//tilt
	//if (pKey->GetKeyState(AZUL_KEY::KEY_SPACE))					//tilt  //tilt
	//{

	//	CameraManger::GetActive()->PedestalUp(movespeed);
	//}
	if (pKey->GetKeyState(AZUL_KEY::KEY_C))					//tilt  //tilt
	{ 

		CameraManger::GetActive()->PedestalDown(movespeed);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))					//tilt  //tilt
	{

		CameraManger::GetActive()->PanLeft(movespeed);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))					//tilt  //tilt
	{

		CameraManger::GetActive()->PanRight(movespeed);
	}

	if (pKey->GetKeyState(AZUL_KEY::KEY_Z))					//Roll
	{



		CameraManger::GetActive()->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm

		//tar = obj;

		Matrix Trans(TRANS, tar);
		Matrix NegTrans(TRANS, -tar);

		Matrix Rot;
		Rot.set(ROT_AXIS_ANGLE, forwardNorm, 0.001f);

		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		CameraManger::GetActive()->setHelper(up, tar, pos);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_X))				//roll
	{



		CameraManger::GetActive()->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm

		//tar = obj;

		Matrix Trans(TRANS, tar);
		Matrix NegTrans(TRANS, -tar);

		Matrix Rot;
		Rot.set(ROT_AXIS_ANGLE, forwardNorm,- 0.001f);

		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		CameraManger::GetActive()->setHelper(up, tar, pos);
	}


	if (pKey->GetKeyState(AZUL_KEY::KEY_P))
	{
		GameObjectManager::HotSwap();
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_SPACE))
	{
		/*Skeleton* pPunchSkeleton = SkeletonManager::Find(Skeleton::Name::HUMANOID_SKELETON_PUNCH);
		pPunchSkeleton->pRigid->rotX += 0.01f;
		Trace::out(" Rot X = %f\n", pPunchSkeleton->pRigid->rotX);*/
	}
}

void MouseTest()
{
	Mouse *pMouse = InputManager::GetMouse();
	
	if (pMouse->GetKeyState(AZUL_MOUSE::BUTTON_RIGHT))					//Dolly
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		CameraManger::GetActive()->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		//	tar = obj;

		pos = pos - 0.01f * forwardNorm;
		tar = tar - 0.01f * forwardNorm;
		CameraManger::GetActive()->setHelper(up, tar, pos);
	}
	if (pMouse->GetKeyState(AZUL_MOUSE::BUTTON_LEFT))				//dolly
	
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		CameraManger::GetActive()->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		// OK, now 3 points... pos, tar, up
		//     now 3 normals... upNorm, forwardNorm, rightNorm
		//	tar = obj;

		pos = pos + 0.01f * forwardNorm;
		tar = tar + 0.01f * forwardNorm;


		CameraManger::GetActive()->setHelper(up, tar, pos);
	}
	
}
