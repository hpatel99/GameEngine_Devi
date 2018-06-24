#ifndef GRAPHICS_OBJECT_MANAGER_H
#define GRAPHICS_OBJECT_MANAGER_H
#include "PCSNode.h"
#include "GraphicsObject.h"
#include "PCSTree.h"
#include "GameObject.h"

class GraphicsObjectManager
{
public:
	static void Add(PCSNode *inNode);
	static void Remove(PCSNode *inNode);
	static GraphicsObject* Find(GraphicsObject::Name inName);
	static void Create();
	static void LoadAllGraphicsObject();
	

private:
	GraphicsObjectManager();
	static GraphicsObjectManager * privInstance();
	static GraphicsObjectManager *pGraphicsObjectManager;
	static void privCreate();
	PCSTree *pRootTree;
};
#endif
