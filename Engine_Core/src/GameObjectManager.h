#ifndef GAMEOBJECT_MANAGER_H
#define GAMEOBJECT_MANAGER_H


#include "PCSTree.h"
#include "GameObject.h"

class GameObjectManager
{
public :
	static void Add(PCSNode *inNode,PCSNode *pParent);

	static void Draw(void);
	static void Update(Time CurrentTime);
	static void Create();
	static void Setup();
	static void HotSwap();
	static PCSTree *GetTree(void);
	static PCSNode *GetRoot();
	static PCSNode* Find(PCSNode*Root, int index);
private:
	GameObjectManager();
	static GameObjectManager *privInstance();
	static GameObjectManager *pGameObjectmanager;
	static void privCreate();
	PCSTree *pRootTree;

	//data memeber

};

#endif
