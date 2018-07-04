/****************************************************************************************

   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.

   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

#include <fbxsdk.h>
#include "Structs.h"
#include <vector>

 

#if defined (FBXSDK_ENV_MAC)
// disable the “format not a string literal and no format arguments” warning since
// the FBXSDK_printf calls made here are all valid calls and there is no secuity risk
#pragma GCC diagnostic ignored "-Wformat-security"
#endif

// Local functions prototype.
void DisplayHierarchy(FbxNode* pNode, int pDepth);

// Keenan(7) - add parent
	static int displayHierarchyIndex = 0;
	void DisplayHierarchy(FbxNode *pParent, FbxNode* pNode, int pDepth, int &parentIndex, int &currentIndex);
	extern  std::vector<ParentChildIndex> PCILIST;
	extern bool isteddy;
	extern int maxdepth;

void DisplayHierarchy(FbxScene* pScene)
{
    int i;
	int parentIndex = -1;
	int curretnIndex = 0;
    FbxNode* lRootNode = pScene->GetRootNode();

    for( i = 0; i < lRootNode->GetChildCount()-1; i++)
    {
		if(isteddy)
		{
			displayHierarchyIndex = 0;
		}
		else
		{
			displayHierarchyIndex = -2;
		}
		// Keenan(7)
			DisplayHierarchy(lRootNode, lRootNode->GetChild(i), 0,curretnIndex,parentIndex );
    }
}

// Keenan(9) - rework below
void DisplayHierarchy(FbxNode *pParent, FbxNode* pNode, int pDepth, int&currentIndex,int & parentIndex)
{
	FbxNodeAttribute::EType lAttrib;
	lAttrib = pNode->GetNodeAttribute()->GetAttributeType();
	FbxNodeAttribute *Attr = pNode->GetNodeAttribute();

	if (pNode->GetNodeAttribute() != nullptr && pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		//getmaxdepth
		if(maxdepth<pDepth)
		{
			maxdepth = pDepth;
		}



		FbxString lString;
		ParentChildIndex ptemp;
		ptemp.myIndex = currentIndex;
		ptemp.parentIndex = parentIndex;
		// Big Hack to remove "Humanoid:" from each name
		char buff[64];
		char buff2[64];
		char origBuff[64];

		// Get original
		// Clean up house cleaning... remove extra stuff on Humanoid
		// Replace spaces with "_" so the names are valid
		strcpy(origBuff, pNode->GetName());

		// test if contains string...
		if (strncmp(origBuff, "Humanoid:", 9) == 0)
		{
			// trim it.
			strcpy(buff, origBuff + 9);
		}
		else
		{
			// leave it
			strcpy(buff, origBuff);
		}
		for (int i = 0; i < (int)strlen(buff); i++)
		{
			// Find a space... replace with an underscore -- quick and dirty
			if (buff[i] == 32)
			{
				buff[i] = 95;
			}
		}

		// Get original
		if (pParent != nullptr)
			strcpy(origBuff, pParent->GetName());

		// test if contains string...
		if (strncmp(origBuff, "Humanoid:", 9) == 0)
		{
			// trim it.
			strcpy(buff2, origBuff + 9);
		}
		else
		{
			// leave it
			strcpy(buff2, origBuff);
		}
		for (int i = 0; i < (int)strlen(buff); i++)
		{
			// Find a space... replace with an underscore -- quick and dirty
			if (buff2[i] == 32)
			{
				buff2[i] = 95;
			}
		}

		strcpy_s(ptemp.NodeName, buff);
		
		PCILIST.emplace_back(ptemp);

		printf("Parent: %d \n",ptemp.parentIndex);
		printf("Current: %d \n", ptemp.myIndex);
		printf(lString.Buffer());
		int index = currentIndex;
		displayHierarchyIndex++;
		
		for (int i = 0; i < pNode->GetChildCount(); i++)
		{
				DisplayHierarchy(pNode, pNode->GetChild(i), pDepth + 1, currentIndex += 1,index);
		}
	}
	else if(pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eNull)
	{
		DisplayHierarchy(pNode, pNode->GetChild(0), pDepth, currentIndex, parentIndex);
	}
}