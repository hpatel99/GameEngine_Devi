#include "GameObjectManager.h"
#include "NullModel.h"
#include "GraphicsObject_Null.h"
#include "ShaderObject.h"
#include "MathEngine.h"
#include "PCSTreeForwardIterator.h"
#include "GameObject.h"
#include "GraphicsObject_Texture.h"
#include "GameObject_Anim.h"

GameObjectManager *GameObjectManager::pGameObjectmanager = 0;//forward declaration for static


void GameObjectManager::Add(PCSNode * inNode,PCSNode *pParent)
{
	assert(inNode != nullptr);
	assert(pParent != nullptr);
	GameObjectManager *pman = GameObjectManager::privInstance();
	
	pman->pRootTree->Insert(inNode,pParent);
}

void GameObjectManager::Draw(void)
{
	GameObjectManager *pGOM = GameObjectManager::privInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	GameObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;
		pGameObj->draw();

		pNode = pForwardIter.Next();
	}
}

void GameObjectManager::Update(Time CurrentTime)
{
	GameObjectManager *pGOM = GameObjectManager::privInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	GameObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;
				 
		pGameObj->Process(CurrentTime);

		pNode = pForwardIter.Next();
	}
}

void GameObjectManager::Create()
{
	privCreate();
}

void GameObjectManager::Setup()
{
	NullModel *Model = new NullModel(0);

	ShaderObject *pShaderNull = new ShaderObject(ShaderObject::Name::NULL_SHADER, "nullRender");

	GraphicsObject_Null *pnullgraphicsobject = new GraphicsObject_Null(Model, pShaderNull);

	GameObject *pGameRoot = new GameObject(pnullgraphicsobject);
	pGameRoot->SetName("GameObject_Root");
	//pGameRoot->setPos(Vect(0.0f, 0.0f, 0.0f));
	GameObjectManager *pman = GameObjectManager::privInstance();
	
	pman->pRootTree->Insert(pGameRoot, pman->pRootTree->GetRoot());
	pman->pRootTree->GetRoot();
	
}

void GameObjectManager::HotSwap()
{
	GameObjectManager *pGOM = GameObjectManager::privInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->GetRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	GameObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;

		if(pGameObj->GetGraphicsObject()->name == GraphicsObject::Name::CUBE_TEXTURE_Brick)
		{
			((GraphicsObject_Texture*)(pGameObj->GetGraphicsObject()))->ChangeTexName(Texture::Name::DUCKWEED);
		}
		pNode = pForwardIter.Next();
	}

}

PCSTree * GameObjectManager::GetTree(void)
{
	GameObjectManager *pGOM = GameObjectManager::privInstance();
	assert(pGOM);
	
	return pGOM->pRootTree;
}

PCSNode * GameObjectManager::GetRoot()
{
	GameObjectManager *pGOM = GameObjectManager::privInstance();
	assert(pGOM);

	return pGOM->pRootTree->GetRoot();
	
}

PCSNode* GameObjectManager::Find(PCSNode * Root, int index)
{
	GameObjectManager *pGOM = GameObjectManager::privInstance();
	assert(pGOM);

	PCSNode *pRootNode = Root->GetParent();	//Hack needs to be solved
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	GameObjectAnim *pGameObj = 0;
	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObjectAnim *)pNode;

		if (pGameObj->indexBoneArray == index)
		{
			return pGameObj;
		}
		pNode = pForwardIter.Next();
	}
	return nullptr;
}



GameObjectManager::GameObjectManager()
{
	//TODO add null object in here
	

	this->pRootTree = new PCSTree();

	
	assert(pRootTree);
}

GameObjectManager * GameObjectManager::privInstance()
{
	return pGameObjectmanager;
}

void GameObjectManager::privCreate()
{
	if(GameObjectManager::pGameObjectmanager== nullptr)
	{
		GameObjectManager::pGameObjectmanager= new GameObjectManager();
		assert(pGameObjectmanager);

	}
}
