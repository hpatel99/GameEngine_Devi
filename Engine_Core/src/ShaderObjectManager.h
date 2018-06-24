#ifndef  SHADER_MANAGER_H
#define SHADER_MANAGER_H
#include "PCSNode.h"
#include "Model.h"
#include "PCSTree.h"
#include "ShaderObject.h"

class ShaderObjectManager
{
public:
	static void Add(PCSNode *inNode);
	static void Remove(PCSNode *inNode);
	static ShaderObject* Find(ShaderObject::Name inname);
	static void Create();
	static void LoadAllShaders();
	

private:
	ShaderObjectManager();
	static ShaderObjectManager * privInstance();
	static ShaderObjectManager *pShaderObjectManager;
	static void privCreate();
	PCSTree *pRootTree;

};



#endif