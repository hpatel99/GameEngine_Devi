#include <sb7.h>
#include"Framework.h"
#include "Game.h"
#include "Texture.h"
#include "InputManager.H"
#include"InputTest.h"
#include "Camera.h"
#include "GameObjectManager.h"
#include "ModelManager.h"
#include "ShaderObjectManager.h"
#include "GraphicsObjectManager.h"
#include "CameraManager.h"
#include "ModelImporter.h"
#include "Time.h"
#include "AnimationManager.h"
#include "SkeletonManager.h"
#include "Skeleton.h"
#include "Clip.h"
#include "Animation.h"
#include "SkeletonLoader.h"
#include "ClipLoader.h"
#include "GraphicsObject_ConstColorSkin.h"
#include "GameObjectRigid.h"
#include "Vect.h"


//hack



//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
Game::Game(const char* windowName, const int Width, const int Height)
	:Engine(windowName, Width, Height)
{
	assert(windowName);//safe gaurd
	this->globalTimer.Tic();
}


//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	InputManager::Create();
	ModelManager::Create();
	ShaderObjectManager::Create();
	GraphicsObjectManager::Create();
	GameObjectManager::Create();
	CameraManger::Create();
	ModelImporter::Create();
	AnimationManager::Create();
	SkeletonManager::Create();
	SkeletonLoader::Create();
	ClipLoader::Create();
}


//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{
	//Adding TExtures
	Texture::Add("Rocks.tga", Texture::Name::ROCKS);
	Texture::Add("Stone.tga", Texture::Name::STONES);
	Texture::Add("RedBrick.tga", Texture::Name::RED_BRICK);
	Texture::Add("Duckweed.tga", Texture::Name::DUCKWEED);
	Texture::Add("FixedTexture2.tga", Texture::Name::SKYBOX_TEXTURE);
	Texture::Add("polarbear.tga", Texture::Name::POLARBEAR);
	//Texture::Add("space_frigate.tga", Texture::Name::SPACE_FRIGATE);
	ModelImporter::Add("Space_Frigate.devi", Model::Name::SPACE_FRIGATE, Texture::Name::SPACE_FRIGATE);
	//ModelImporter::Add("astroboy.devi", Model::Name::ASTROBOY, Texture::Name::ASTROBOY);
	ModelImporter::Add("buggy.devi", Model::Name::BUGGY, Texture::Name::BUGGY);
	ModelImporter::Add("warbear.devi", Model::Name::WARBEAR, Texture::Name::WARBEAR);
	ModelImporter::Add("Geth_Trooper.devi", Model::Name::GETHWARRIOR, Texture::Name::GETHWARRIOR);
	
	
	
	
	
	//Camera Setup
	Camera *pCam = new Camera();						//Space frigate Camera
	pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
	pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 1.0f, 1000.0f);
	pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 0.0f, 100.0f));
	pCam->updateCamera();

	CameraManger::Add(pCam);
	CameraManger::pCameraManager->pFrustrumRender = pCam;

	
	
	
	GameObjectManager::Setup();// HAck for access violation shall fix

	//Loading all known Models
	ModelManager::LoadAllModels();

	//initialize shaderobject
	ShaderObjectManager::LoadAllShaders();

	//initalize all graphics 
	GraphicsObjectManager::LoadAllGraphicsObject();
	//Animation hard setup
	// setup relationship and hierarchy
	//SetAnimationHierarchy();

	////////////////////////////////////////////////////////////////////////
	//           Skeleton Creation and adding to manager			     //
	///////////////////////////////////////////////////////////////////////

	SkeletonLoader::Add("humanoid.skel", 0.1f,"BoneInverseHuman.bones", Skeleton::Name::HUMANOID_SKELETON_PUNCH_UNCOMPRESSED);	//one for each animation in display
	SkeletonLoader::Add("humanoid.skel", 0.1f, "BoneInverseHuman.bones",Skeleton::Name::HUMANOID_SKELETON_SHOT);
	//SkeletonLoader::Add("teddy.skel", 10.0f, "BoneInverseteddy.bones", Skeleton::Name::TEDDY_SKELETON_IDLE);
	//SkeletonLoader::Add("teddy.skel", 10.0f, "BoneInverseteddy.bones", Skeleton::Name::TEDDY_SKELETON_WALK);

	//pPunch_Skeleton->pRigid->setPos(Vect(0.0f, 0.0f, 0.0f));
	//pPunch_Skeleton->pRigid->rotate(Rot3AxisType::ROT_XYZ, 0.0f, 0.0f, 0.0f);
	////////////////////////////////////////////////////////////////////////
	//           Animation Creation and adding to manager			     //
	///////////////////////////////////////////////////////////////////////
	/*Animation *p_animation = new Animation(Skeleton::Name::TEDDY_SKELETON_WALK,Animation::Name::TEDDY_ANIMATION_WALK);
	AnimationManager::Add(p_animation);

	p_animation = new Animation(Skeleton::Name::TEDDY_SKELETON_IDLE, Animation::Name::TEDDY_ANIMATION_IDLE);
	AnimationManager::Add(p_animation);*/

	Animation *p_animation = new Animation(Skeleton::Name::HUMANOID_SKELETON_PUNCH_UNCOMPRESSED, Animation::Name::HUMANOID_ANIMATION_PUNCH);
	AnimationManager::Add(p_animation);

	//p_animation = new Animation(Skeleton::Name::HUMANOID_SKELETON_SHOT, Animation::Name::HUMANOID_ANIMATION_SHOT);
	//AnimationManager::Add(p_animation);



	// initialize animation data

	Clip *clip;
	/*clip= ClipLoader::Add("shot.animo",Clip::Name::HUMANOID_SHOT);
	p_animation = AnimationManager::Find(Animation::Name::HUMANOID_ANIMATION_SHOT);
	p_animation->AddClip(clip);
	p_animation->pActiveClip = clip;*/
	
	clip = ClipLoader::Add("punch.animo", Clip::Name::HUMANOID_PUNCH);
	p_animation = AnimationManager::Find(Animation::Name::HUMANOID_ANIMATION_PUNCH);
	p_animation->AddClip(clip);
	p_animation->pActiveClip = clip;

	/*clip = ClipLoader::Add("idle.animo", Clip::Name::TEDDY_IDLE);
	p_animation = AnimationManager::Find(Animation::Name::TEDDY_ANIMATION_IDLE);
	p_animation->AddClip(clip);
	p_animation->pActiveClip = clip;
	
	clip = ClipLoader::Add("walk.animo", Clip::Name::TEDDY_WALK);
	p_animation = AnimationManager::Find(Animation::Name::TEDDY_ANIMATION_WALK);
	p_animation->AddClip(clip);
	p_animation->pActiveClip = clip;*/
	//SetAnimationData();

	
	//variables to set
	
	
	
	GameObjectRigid *pGameObj;
	//create gameobject 
	
	////Skybox below

	//pGameObj = new GameObject(GraphicsObjectManager::Find(GraphicsObject::SKYBOX_TEXTURE));
	//pGameObj->setPos(Vect(0.0f, 0.0f, 0.0f));
	//pGameObj->setScale(Vect(200.0f, 200.0f,200.0f));
	//pGameObj->rotate(ROT_XYZ, 0.0f, 0.0f, MATH_PI);
	//assert(pGameObj);
	//GameObjectManagerager::Add(pGameObj);
	//
	//sphere BElow
	/*pGameObj = new GameObject(GraphicsObjectManager::Find(GraphicsObject::SPHERE_WIREFRAME));
	pGameObj->setScale(Vect(1.0f, 1.0f, 1.0f));*/
	
	//CameraModel
	/*pGameObj = new GameObject(GraphicsObjectManager::Find(GraphicsObject::CAMERAMODEL_WIREFRAME));
	GameObjectManagerager::Add(pGameObj);
	*/

	//ModelImporter::AddSkinedModel("TeddySkin.rig", Model::Name::TEDDY_SKINNING_MODEL);			//importing all fbx skinnign once we load everything else
	ModelImporter::AddSkinedModel("HumanoidSkin.rig", Model::Name::HUMANOID_SKINNING_MODEL);			//importing all fbx skinnign once we load everything else
	
	
	////////////////////////////////////////////////////////////////////////
	//          Graphics obj Creation and adding to manager			     //
	///////////////////////////////////////////////////////////////////////

	/*GraphicsObject *pGraph = new GraphicsObject_ConstColorSkin(ModelManager::Find(Model::TEDDY_SKINNING_MODEL), ShaderObjectManager::Find(ShaderObject::GPU_SKINNIG), SkeletonManager::Find(Skeleton::Name::TEDDY_SKELETON_IDLE), AnimationManager::Find(Animation::Name::TEDDY_ANIMATION_IDLE), GraphicsObject::Name::SKINNING_TEDDY_IDLE);
	GraphicsObjectManager::Add(pGraph);

	pGraph = new GraphicsObject_ConstColorSkin(ModelManager::Find(Model::TEDDY_SKINNING_MODEL), ShaderObjectManager::Find(ShaderObject::GPU_SKINNIG), SkeletonManager::Find(Skeleton::Name::TEDDY_SKELETON_WALK), AnimationManager::Find(Animation::Name::TEDDY_ANIMATION_WALK), GraphicsObject::Name::SKINNING_TEDDY_WALK);
	GraphicsObjectManager::Add(pGraph);*/

	GraphicsObject *pGraph = new GraphicsObject_ConstColorSkin(ModelManager::Find(Model::HUMANOID_SKINNING_MODEL), ShaderObjectManager::Find(ShaderObject::GPU_SKINNIG), SkeletonManager::Find(Skeleton::Name::HUMANOID_SKELETON_PUNCH_UNCOMPRESSED),AnimationManager::Find(Animation::Name::HUMANOID_ANIMATION_PUNCH) ,GraphicsObject::Name::SKINNING_HUMAN_PUNCH);
	GraphicsObjectManager::Add(pGraph);

	//pGraph = new GraphicsObject_ConstColorSkin(ModelManager::Find(Model::HUMANOID_SKINNING_MODEL), ShaderObjectManager::Find(ShaderObject::GPU_SKINNIG), SkeletonManager::Find(Skeleton::Name::HUMANOID_SKELETON_SHOT), AnimationManager::Find(Animation::Name::HUMANOID_ANIMATION_SHOT), GraphicsObject::Name::SKINNING_HUMAN_SHOT);
	//GraphicsObjectManager::Add(pGraph);
	
	////////////////////////////////////////////////////////////////////////
	//          Game   obj Creation and adding to manager			     //
	///////////////////////////////////////////////////////////////////////


	/*pGameObj = new GameObjectRigid(GraphicsObjectManager::Find(GraphicsObject::SKINNING_TEDDY_WALK));
	GameObjectManager::Add(pGameObj, GameObjectManager::GetRoot());

	pGameObj = new GameObjectRigid(GraphicsObjectManager::Find(GraphicsObject::SKINNING_TEDDY_IDLE));
	GameObjectManager::Add(pGameObj, GameObjectManager::GetRoot());*/

	//pGameObj = new GameObjectRigid(GraphicsObjectManager::Find(GraphicsObject::SKINNING_HUMAN_SHOT));
	//GameObjectManager::Add(pGameObj, GameObjectManager::GetRoot());

	pGameObj = new GameObjectRigid(GraphicsObjectManager::Find(GraphicsObject::SKINNING_HUMAN_PUNCH));
	GameObjectManager::Add(pGameObj, GameObjectManager::GetRoot());
	//((GraphicsObject_ConstColorSkin*)pGameObj->GetGraphicsObject());
	//Game object added now will set it to porper orientation
	
	//p_skeleton->pRigid->setPos(Vect(10.0f, -30.0f, -70.0f));
	//p_skeleton->pRigid->rotate(Rot3AxisType::ROT_XYZ, -1.5708f, 0.0f, 0.00f);
	SkeletonManager::Find(Skeleton::Name::HUMANOID_SKELETON_PUNCH_UNCOMPRESSED)->pRigid->setPos(Vect(70.0f, -70.0f, -150.0f));
	SkeletonManager::Find(Skeleton::Name::HUMANOID_SKELETON_PUNCH_UNCOMPRESSED)->pRigid->rotate(Rot3AxisType::ROT_XYZ, -1.5708f, 0.0f, 0.00f);
	
}


//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Game::Update(float )
{
	static Time tCurrent(Time::ZERO);
	KeyboardTest();//check before swapping camera a:D

	MouseTest();

	//updateing camera
	CameraManger::Update();

	// Animate ME
	//ProcessAnimation(tCurrent);
	AnimationManager::Update();				//lerp slerp lerp on all the bones is done accordingly to the time
	// upadting the gameobjects
	GameObjectManager::Update(this->globalTimer.Toc());
#if 0
	Skeleton *pSkel = SkeletonManager::Find(Skeleton::Name::HUMANOID_SKELETON_PUNCH);
	Animation *Ani = AnimationManager::Find(Animation::Name::HUMANOID_ANIMATION_PUNCH);
	Matrix *peval =(Matrix*)Ani->pBit_ssbo->MapData(ShaderBufferObject::READ_ONLY);
	
	for (int i = 0 ; pSkel->numbones;i++)
	{
		assert(peval[i][m0] == pSkel->pWorldOfBones[i][m0]);
		assert(peval[i][m1] == pSkel->pWorldOfBones[i][m1]);
		assert(peval[i][m2] == pSkel->pWorldOfBones[i][m2]);
		assert(peval[i][m3] == pSkel->pWorldOfBones[i][m3]);
		assert(peval[i][m4] == pSkel->pWorldOfBones[i][m4]);
		assert(peval[i][m5] == pSkel->pWorldOfBones[i][m5]);
		assert(peval[i][m6] == pSkel->pWorldOfBones[i][m6]);
		assert(peval[i][m7] == pSkel->pWorldOfBones[i][m7]);
		assert(peval[i][m8] == pSkel->pWorldOfBones[i][m8]);
		assert(peval[i][m9] == pSkel->pWorldOfBones[i][m9]);
		assert(peval[i][m10] == pSkel->pWorldOfBones[i][m10]);
		assert(peval[i][m11] == pSkel->pWorldOfBones[i][m11]);
		assert(peval[i][m12] == pSkel->pWorldOfBones[i][m12]);
		assert(peval[i][m13] == pSkel->pWorldOfBones[i][m13]);
		assert(peval[i][m14] == pSkel->pWorldOfBones[i][m14]);
		assert(peval[i][m15] == pSkel->pWorldOfBones[i][m15]);
	}
	Ani->pBit_ssbo->UnMapData();
#endif


	SkeletonManager::Update();				// over here the updat of the QST is send to the bones and not game object.		
	//SetAnimationPose(pFirstBone, tCurrent);
	

}


//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{// drawing the game objects
	GameObjectManager::Draw();
}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{	//TODO add deletes clean for god sake
  //  glDeleteVertexArrays(1, &vao);
   // glDeleteProgram(pGameObj->GetGraphicsObject()->programObject);
  //  glDeleteBuffers(1, &buffer);
}




//------------------------------------------------------------------
// Game::ClearBufferFunc()
// Allows user to change the way the clear buffer function works
//------------------------------------------------------------------
void Game::ClearBufferFunc()
{
	const GLfloat grey[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, grey);
	glClearBufferfv(GL_DEPTH, 0, &one);
}
