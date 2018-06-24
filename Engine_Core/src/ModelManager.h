#ifndef  MODEL_MANAGER_H
#define MODEL_MANAGER_H
#include "PCSNode.h"
#include "Model.h"
#include "PCSTree.h"

class ModelManager
{
public: 
	static void Add(PCSNode *inNode);
	//Todo: ADd remove in maanagers
	static void Remove(PCSNode *inNode);//
	static Model* Find(Model::Name inname);
	static void Create();
	static void LoadAllModels();

private :
	ModelManager();
	static ModelManager * privInstance();
	static ModelManager *pModelManager;
	static void privCreate();
	PCSTree *pRootTree;

};



#endif