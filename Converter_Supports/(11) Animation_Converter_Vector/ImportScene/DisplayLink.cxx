/****************************************************************************************

   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.

   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.

****************************************************************************************/

#include "DisplayLink.h"
#include <vector>
#include "Structs.h"
#if defined (FBXSDK_ENV_MAC)
// disable the “format not a string literal and no format arguments” warning since
// the FBXSDK_printf calls made here are all valid calls and there is no secuity risk
#pragma GCC diagnostic ignored "-Wformat-security"
#endif
int findindexbyName( char * name);
extern std::vector<ParentChildIndex> PCILIST;
extern std::vector<SkinVerts> skinverts;
extern std::vector<Matrix> worldinverse;

void DisplayLink(FbxGeometry* pGeometry)
{
    //Display cluster now

    //int i, lLinkCount;
    //FbxCluster* lLink;
	Matrix *Temp = new Matrix();
	worldinverse.reserve(PCILIST.size());
	for ( unsigned int i = 0; i < PCILIST.size(); i++)
	{
		worldinverse.push_back(*Temp);

	}
    int i, j;
    int lSkinCount=0;
    int lClusterCount=0;
    FbxCluster* lCluster;

    lSkinCount=pGeometry->GetDeformerCount(FbxDeformer::eSkin);



    //lLinkCount = pGeometry->GetLinkCount();
    for(i=0; i!=lSkinCount; ++i)
    {
        lClusterCount = ((FbxSkin *) pGeometry->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
        for (j = 0; j != lClusterCount; ++j)			//for each clusters bones, 

        {
            DisplayInt("    Cluster ", i);
			DisplayInt("    Bone number", j);
            lCluster=((FbxSkin *) pGeometry->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);
            //lLink = pGeometry->GetLink(i);    

            const char* lClusterModes[] = { "Normalize", "Additive", "Total1" };

            DisplayString("    Mode: ", lClusterModes[lCluster->GetLinkMode()]);

            if(lCluster->GetLink() != NULL)
            {
                DisplayString("        Name: ", (char *) lCluster->GetLink()->GetName());
            }
			int idx = findindexbyName((char *)lCluster->GetLink()->GetName());
            FbxString lString1 = "        Link Indices: ";
            FbxString lString2 = "        Weight Values: ";

            int k, lIndexCount = lCluster->GetControlPointIndicesCount();
            int* lIndices = lCluster->GetControlPointIndices();
            double* lWeights = lCluster->GetControlPointWeights();

            for(k = 0; k < lIndexCount; k++)		//going through each indexes
            {
				WeightTuple temp;
				temp.index = idx;
				temp.weight =(float) lWeights[k];

				skinverts[lIndices[k]].Weight.push_back(temp);
                lString1 += lIndices[k];
                lString2 += (float) lWeights[k];

                if (k < lIndexCount - 1)
                {
                    lString1 += ", ";
                    lString2 += ", ";
                }
            }

            lString1 += "\n";
            lString2 += "\n";

            FBXSDK_printf(lString1);
            FBXSDK_printf(lString2);

            DisplayString("");

            FbxAMatrix lMatrix,nMatrix,mMatrix;

			lMatrix = lCluster->GetTransformLinkMatrix(nMatrix).Inverse() * lCluster->GetTransformMatrix(mMatrix);

			worldinverse[idx][m0] =(float)  lMatrix[0][0];
			worldinverse[idx][m1] =(float)  lMatrix[0][1];
			worldinverse[idx][m2] =(float)  lMatrix[0][2];
			worldinverse[idx][m3] =(float)  lMatrix[0][3];
							  	 
			worldinverse[idx][m4] =(float)  lMatrix[1][0];
			worldinverse[idx][m5] =(float) lMatrix[1][1];
			worldinverse[idx][m6] =(float) lMatrix[1][2];
			worldinverse[idx][m7] =(float) lMatrix[1][3];
							 	 
			worldinverse[idx][m8] =(float)  lMatrix[2][0];
			worldinverse[idx][m9] =(float) lMatrix[2][1];
			worldinverse[idx][m10]=(float) lMatrix[2][2];
			worldinverse[idx][m11]=(float) lMatrix[2][3];
								 
			worldinverse[idx][m12]=(float) lMatrix[3][0];
			worldinverse[idx][m13]=(float) lMatrix[3][1];
			worldinverse[idx][m14]=(float) lMatrix[3][2];
			worldinverse[idx][m15]=(float) lMatrix[3][3];



            
           /* Display3DVector("        Transform Translation: ", lMatrix.GetT());
            Display3DVector("        Transform Rotation: ", lMatrix.GetR());
            Display3DVector("        Transform Scaling: ", lMatrix.GetS());

            
            Display3DVector("        Transform Link Translation: ", lMatrix.GetT());
            Display3DVector("        Transform Link Rotation: ", lMatrix.GetR());
            Display3DVector("        Transform Link Scaling: ", lMatrix.GetS());*/

            if (lCluster->GetAssociateModel() != NULL)
            {
                lMatrix = lCluster->GetTransformAssociateModelMatrix(lMatrix);
                DisplayString("        Associate Model: ", (char *) lCluster->GetAssociateModel()->GetName());
                Display3DVector("        Associate Model Translation: ", lMatrix.GetT());
                Display3DVector("        Associate Model Rotation: ", lMatrix.GetR());
                Display3DVector("        Associate Model Scaling: ", lMatrix.GetS());
            }

            DisplayString("");
        }
    }
}

int  findindexbyName( char * name)
{
	int index= -1;

	if (strncmp(name, "Humanoid:", 9) == 0)
	{
		name += 9;
	}
	
	for (int i = 0; i < (int)strlen(name); i++)
		{
			// Find a space... replace with an underscore -- quick and dirty
			if (name[i] == 32)
			{
				name[i] = 95;
			}
		}


	for (int i = 0; i < (signed)PCILIST.size(); i++)
	{
		if (strcmp(name, PCILIST[i].NodeName) == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}

