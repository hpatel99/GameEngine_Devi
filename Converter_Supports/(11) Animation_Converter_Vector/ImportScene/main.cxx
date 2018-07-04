/****************************************************************************************

   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.

   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.

****************************************************************************************/

/////////////////////////////////////////////////////////////////////////
//
// This example illustrates how to detect if a scene is password 
// protected, import and browse the scene to access node and animation 
// information. It displays the content of the FBX file which name is 
// passed as program argument. You can try it with the various FBX files 
// output by the export examples.
//
/////////////////////////////////////////////////////////////////////////

#include "../Common/Common.h"
#include "DisplayCommon.h"
#include "DisplayHierarchy.h"
#include "DisplayAnimation.h"
#include "DisplayMarker.h"
#include "DisplaySkeleton.h"
#include "DisplayMesh.h"
#include "DisplayNurb.h"
#include "DisplayPatch.h"
#include "DisplayLodGroup.h"
#include "DisplayCamera.h"
#include "DisplayLight.h"
#include "DisplayGlobalSettings.h"
#include "DisplayPose.h"
#include "DisplayPivotsAndLimits.h"
#include "DisplayUserProperties.h"
#include "Structs.h"
#include "DisplayGenericInfo.h"
#include <vector>
#include "File.h"
#include <algorithm>


// Local function prototypes.
void DisplayContent(FbxScene* pScene);
void DisplayContent(FbxNode* pNode);
void DisplayTarget(FbxNode* pNode);
void DisplayTransformPropagation(FbxNode* pNode);
void DisplayGeometricTransform(FbxNode* pNode);
void DisplayMetaData(FbxScene* pScene);
void CreateTableofBones();
void GetSkeletonInFile();
void GetSkinInFile();

static bool gVerbose = true;
std::vector<ParentChildIndex> PCILIST ;
BoneHeader BoneHDR;
ClipHeader *ClipHDR;
std::vector<FrameBucketNodes> FrmBcknode;
std::vector<FrameBoneNodes>FrmBnenode;
bool isteddy;
std::vector<SkinVerts> skinverts;
std::vector<Matrix> worldinverse;
std::vector<FBX_Trilist> triList;
std::vector<Vert_xyzuvn> OutVerts;
std::vector<BoneIndex> OutIndex;
std::vector<BoneWeight> OutWeight;
std::vector<TableEntry> HierTable;
int maxdepth;


int main(int argc, char** argv)
{
    FbxManager* lSdkManager = NULL;
    FbxScene* lScene = NULL;
    bool lResult;

    // Prepare the FBX SDK.
    InitializeSdkObjects(lSdkManager, lScene);
    // Load the scene.
	maxdepth = 1;
    // The example can take a FBX file as an argument.
	FbxString lFilePath("");
	for( int i = 1, c = argc; i < c; ++i )
	{
		if( FbxString(argv[i]) == "-test" ) gVerbose = false;
		else if( lFilePath.IsEmpty() ) lFilePath = argv[i];
	}

	if( lFilePath.IsEmpty() )
	{
        lResult = false;
        FBXSDK_printf("\n\nUsage: ImportScene <FBX file name>\n\n");
	}
	else
	{
		FBXSDK_printf("\n\nFile: %s\n\n", lFilePath.Buffer());
		lResult = LoadScene(lSdkManager, lScene, lFilePath.Buffer());
	}
	if(strcmp("teddy_TGA.fbx", lFilePath.Buffer()) == 0)
	{
		isteddy = true;
	}
    if(lResult == false)
    {
        FBXSDK_printf("\n\nAn error occurred while loading the scene...");
    }
    else 
    {
        // Display the scene.
        DisplayMetaData(lScene);

        FBXSDK_printf("\n\n---------------------\nGlobal Light Settings\n---------------------\n\n");

        if( gVerbose ) DisplayGlobalLightSettings(&lScene->GetGlobalSettings());

        FBXSDK_printf("\n\n----------------------\nGlobal Camera Settings\n----------------------\n\n");

        if( gVerbose ) DisplayGlobalCameraSettings(&lScene->GetGlobalSettings());

        FBXSDK_printf("\n\n--------------------\nGlobal Time Settings\n--------------------\n\n");

        if( gVerbose ) DisplayGlobalTimeSettings(&lScene->GetGlobalSettings());

        FBXSDK_printf("\n\n---------\nHierarchy\n---------\n\n");

        if( gVerbose ) DisplayHierarchy(lScene);
		maxdepth++;  //cause zero is not zero but it is index(confused??? me too)
		//Harsh
		//Time to write skeleton
		BoneHDR.Numbones = PCILIST.size();
		BoneHDR.MaxDepth = maxdepth;
		CreateTableofBones();
		GetSkeletonInFile();
        FBXSDK_printf("\n\n------------\nNode Content\n------------\n\n");
		
        if( gVerbose ) DisplayContent(lScene);

        FBXSDK_printf("\n\n----\nPose\n----\n\n");

        if( gVerbose ) DisplayPose(lScene);

        FBXSDK_printf("\n\n---------\nAnimation\n---------\n\n");
	   
        if( gVerbose ) DisplayAnimation(lScene);

        //now display generic information

		// Keenan(2) - Reduce Prints
		// FBXSDK_printf("\n\n---------\nGeneric Information\n---------\n\n");
		// if( gVerbose ) DisplayGenericInfo(lScene);

		//lets sort now

		for (unsigned int i = 0; i < skinverts.size(); i++)	//sort and reverse to have bone weight in the desending order
		{
			std::sort(skinverts[i].Weight.begin(),skinverts[i].Weight.end());
			std::reverse(skinverts[i].Weight.begin(), skinverts[i].Weight.end());
		}
		WeightTuple replacingvalue;
		replacingvalue.index = 0;
		replacingvalue.weight = 0.0f;
		for (unsigned int i = 0; i < skinverts.size(); i++)	//resize everything 
		{

			skinverts[i].Weight.resize(4,replacingvalue);
		}
		for (unsigned int i = 0; i < skinverts.size(); i++)	// normalize the weights
		{
			float total = skinverts[i].Weight[0].weight + skinverts[i].Weight[1].weight + skinverts[i].Weight[2].weight + skinverts[i].Weight[3].weight;
			skinverts[i].Weight[0].weight /= total;
			skinverts[i].Weight[1].weight /= total;
			skinverts[i].Weight[2].weight /= total;
			skinverts[i].Weight[3].weight /= total;


		}

	}

	
	
	Vert_xyzuvn tempVert;
	BoneIndex tempindex;
	BoneWeight tempweight;
	for (unsigned int i = 0; i < skinverts.size(); i++)
	{
		tempVert.u = 0;
		tempVert.v = 0;
		tempVert.x = skinverts[i].x;
		tempVert.y = skinverts[i].y;
		tempVert.z = skinverts[i].z;
		tempVert.nx = skinverts[i].nx;
		tempVert.ny = skinverts[i].ny;
		tempVert.nz = skinverts[i].nz;
		OutVerts.push_back(tempVert);
		tempindex.Index[0] = skinverts[i].Weight[0].index;
		tempindex.Index[1] = skinverts[i].Weight[1].index;
		tempindex.Index[2] = skinverts[i].Weight[2].index;
		tempindex.Index[3] = skinverts[i].Weight[3].index;
		OutIndex.push_back(tempindex);
		tempweight.Index[0] = skinverts[i].Weight[0].weight;
		tempweight.Index[1] = skinverts[i].Weight[1].weight;
		tempweight.Index[2] = skinverts[i].Weight[2].weight;
		tempweight.Index[3] = skinverts[i].Weight[3].weight;
		OutWeight.push_back(tempweight);
	}





	GetSkinInFile();

    // Destroy all objects created by the FBX SDK.
    DestroySdkObjects(lSdkManager, lResult);

    return 0;
}

void DisplayContent(FbxScene* pScene)
{
    int i;
    FbxNode* lNode = pScene->GetRootNode();

    if(lNode)
    {
        for(i = 0; i < lNode->GetChildCount(); i++)
        {
            DisplayContent(lNode->GetChild(i));
        }
    }
}

void CreateTableofBones()
{
	HierTable.reserve(BoneHDR.Numbones);

	int rec=0;
	ParentChildIndex pCurrent;
	
	while (rec < BoneHDR.Numbones)
	{
		pCurrent = PCILIST[rec];
		TableEntry temp ;
		temp.Hier.reserve(maxdepth);
		while (pCurrent.parentIndex != -1)
		{
			temp.Hier.push_back(pCurrent.myIndex);

			pCurrent = PCILIST[pCurrent.parentIndex];

		}
		temp.Hier.push_back(0);
		HierTable.emplace_back(temp);
		rec++;
	}
	//reverse the order cause thats how we will get to local
	int j = 0;
	
	while (j < HierTable.size())
	{
		std::reverse(HierTable[j].Hier.begin(), HierTable[j].Hier.end());
		j++;
	}
	j = 0;
	int newvalue = -1;
	while (j < HierTable.size())
	{
		HierTable[j].Hier.resize(maxdepth, newvalue);
		j++;
	}

	_FbxTrace("Lol");
}




void GetSkeletonInFile()
{
	int j = 0;
	File::Handle fh;
	File::Open(fh, "Skely.skel", File::WRITE);
	File::Write(fh, &BoneHDR, sizeof(BoneHeader));
	File::Write(fh, PCILIST.data(),PCILIST.size()*sizeof(ParentChildIndex) );
	while(j<HierTable.size())
	{
		File::Write(fh, HierTable[j].Hier.data(), maxdepth * sizeof(int));
		j++;
	}
	File::Flush(fh);
	File::Close(fh);
}
void GetSkinInFile()
{
	SkinHeader ski;
	ski.NumOfTris = triList.size();
	ski.NumOfVerts = skinverts.size();
	File::Handle fh;
	File::Open(fh, "Skins.rig", File::WRITE);
	File::Write(fh, &ski, sizeof(SkinHeader));
	File::Write(fh, OutVerts.data(), OutVerts.size() * sizeof(Vert_xyzuvn));	// writing verts
	File::Write(fh, OutIndex.data(), OutIndex.size() * sizeof(BoneIndex));		// indexing
	File::Write(fh, OutWeight.data(), OutWeight.size() * sizeof(BoneWeight));	// weights


	File::Write(fh, triList.data(), triList.size() * sizeof(FBX_Trilist));		//triangles

	File::Flush(fh);
	File::Close(fh);

	File::Handle fh2;
	File::Open(fh2, "BoneInverseteddy.bones", File::WRITE);
	File::Write(fh2, &BoneHDR, sizeof(BoneHeader));
	File::Write(fh2, worldinverse.data(), worldinverse.size() * sizeof(Matrix));
	File::Flush(fh2);
	File::Close(fh2);


}
void DisplayContent(FbxNode* pNode)
{
    FbxNodeAttribute::EType lAttributeType;
    int i;

    if(pNode->GetNodeAttribute() == NULL)
    {
        FBXSDK_printf("NULL Node Attribute\n\n");
    }
    else
    {
        lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

        switch (lAttributeType)
        {
	    default:
	        break;
        case FbxNodeAttribute::eMarker:  
            DisplayMarker(pNode);
            break;

        case FbxNodeAttribute::eSkeleton:  
            DisplaySkeleton(pNode);
            break;

        case FbxNodeAttribute::eMesh:      
            DisplayMesh(pNode);
            break;

        case FbxNodeAttribute::eNurbs:      
            DisplayNurb(pNode);
            break;

        case FbxNodeAttribute::ePatch:     
            DisplayPatch(pNode);
            break;

        case FbxNodeAttribute::eCamera:    
            DisplayCamera(pNode);
            break;

        case FbxNodeAttribute::eLight:     
            DisplayLight(pNode);
            break;

        case FbxNodeAttribute::eLODGroup:
            DisplayLodGroup(pNode);
            break;
        }   
    }

    DisplayUserProperties(pNode);
    DisplayTarget(pNode);
    DisplayPivotsAndLimits(pNode);
    DisplayTransformPropagation(pNode);
    DisplayGeometricTransform(pNode);

    for(i = 0; i < pNode->GetChildCount(); i++)
    {
        DisplayContent(pNode->GetChild(i));
    }
}


void DisplayTarget(FbxNode* pNode)
{
    if(pNode->GetTarget() != NULL)
    {
        DisplayString("    Target Name: ", (char *) pNode->GetTarget()->GetName());
    }
}

void DisplayTransformPropagation(FbxNode* pNode)
{
    FBXSDK_printf("    Transformation Propagation\n");

    // 
    // Rotation Space
    //
    EFbxRotationOrder lRotationOrder;
    pNode->GetRotationOrder(FbxNode::eSourcePivot, lRotationOrder);

    FBXSDK_printf("        Rotation Space: ");

    switch (lRotationOrder)
    {
    case eEulerXYZ: 
        FBXSDK_printf("Euler XYZ\n");
        break;
    case eEulerXZY:
        FBXSDK_printf("Euler XZY\n");
        break;
    case eEulerYZX:
        FBXSDK_printf("Euler YZX\n");
        break;
    case eEulerYXZ:
        FBXSDK_printf("Euler YXZ\n");
        break;
    case eEulerZXY:
        FBXSDK_printf("Euler ZXY\n");
        break;
    case eEulerZYX:
        FBXSDK_printf("Euler ZYX\n");
        break;
    case eSphericXYZ:
        FBXSDK_printf("Spheric XYZ\n");
        break;
    }

    //
    // Use the Rotation space only for the limits
    // (keep using eEulerXYZ for the rest)
    //
    FBXSDK_printf("        Use the Rotation Space for Limit specification only: %s\n",
        pNode->GetUseRotationSpaceForLimitOnly(FbxNode::eSourcePivot) ? "Yes" : "No");


    //
    // Inherit Type
    //
    FbxTransform::EInheritType lInheritType;
    pNode->GetTransformationInheritType(lInheritType);

    FBXSDK_printf("        Transformation Inheritance: ");

    switch (lInheritType)
    {
    case FbxTransform::eInheritRrSs:
        FBXSDK_printf("RrSs\n");
        break;
    case FbxTransform::eInheritRSrs:
        FBXSDK_printf("RSrs\n");
        break;
    case FbxTransform::eInheritRrs:
        FBXSDK_printf("Rrs\n");
        break;
    }
}

void DisplayGeometricTransform(FbxNode* pNode)
{
	FBX_UNUSED(pNode);

// Keenan(7)
#if 0

    FbxVector4 lTmpVector;

    FBXSDK_printf("    Geometric Transformations\n");

    //
    // Translation
    //
    lTmpVector = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FBXSDK_printf("        Translation: %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

    //
    // Rotation
    //
    lTmpVector = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FBXSDK_printf("        Rotation:    %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

    //
    // Scaling
    //
    lTmpVector = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
    FBXSDK_printf("        Scaling:     %f %f %f\n", lTmpVector[0], lTmpVector[1], lTmpVector[2]);

// Keenan(7)
#endif
}


void DisplayMetaData(FbxScene* pScene)
{
    FbxDocumentInfo* sceneInfo = pScene->GetSceneInfo();
    if (sceneInfo)
    {
        FBXSDK_printf("\n\n--------------------\nMeta-Data\n--------------------\n\n");
        FBXSDK_printf("    Title: %s\n", sceneInfo->mTitle.Buffer());
        FBXSDK_printf("    Subject: %s\n", sceneInfo->mSubject.Buffer());
        FBXSDK_printf("    Author: %s\n", sceneInfo->mAuthor.Buffer());
        FBXSDK_printf("    Keywords: %s\n", sceneInfo->mKeywords.Buffer());
        FBXSDK_printf("    Revision: %s\n", sceneInfo->mRevision.Buffer());
        FBXSDK_printf("    Comment: %s\n", sceneInfo->mComment.Buffer());

        FbxThumbnail* thumbnail = sceneInfo->GetSceneThumbnail();
        if (thumbnail)
        {
            FBXSDK_printf("    Thumbnail:\n");

            switch (thumbnail->GetDataFormat())
            {
            case FbxThumbnail::eRGB_24:
                FBXSDK_printf("        Format: RGB\n");
                break;
            case FbxThumbnail::eRGBA_32:
                FBXSDK_printf("        Format: RGBA\n");
                break;
            }

            switch (thumbnail->GetSize())
            {
	        default:
	            break;
            case FbxThumbnail::eNotSet:
                FBXSDK_printf("        Size: no dimensions specified (%ld bytes)\n", thumbnail->GetSizeInBytes());
                break;
            case FbxThumbnail::e64x64:
                FBXSDK_printf("        Size: 64 x 64 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
                break;
            case FbxThumbnail::e128x128:
                FBXSDK_printf("        Size: 128 x 128 pixels (%ld bytes)\n", thumbnail->GetSizeInBytes());
            }
        }
    }
}

