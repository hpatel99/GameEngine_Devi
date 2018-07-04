/****************************************************************************************

   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.

   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.

****************************************************************************************/

#include "DisplayCommon.h"
#include "DisplayAnimation.h"
#include "Structs.h"
#include <iso646.h>
#include <vector>
#include "File.h"
#include "Util.h"

#if defined (FBXSDK_ENV_MAC)
// disable the “format not a string literal and no format arguments” warning since
// the FBXSDK_printf calls made here are all valid calls and there is no secuity risk
#pragma GCC diagnostic ignored "-Wformat-security"
#endif

// Keenan(10)
static int indexChannels = 0;

// Keenan(11)
FbxAnimEvaluator *pAnimEvaluator;
extern  BoneHeader BoneHDR;
extern bool isteddy;
extern std::vector<FrameBucketNodes> FrmBcknode;
extern std::vector<FrameBoneNodes>FrmBnenode;
extern ClipHeader *ClipHDR;


// Keenan(8) - add FbxTime lkeyTime to display
void DisplayAnimationKeenan(FbxAnimLayer* pAnimLayer, FbxNode* pNode, bool isSwitcher, FbxTime lKeyTime);
void DisplayChannelsKeenan(FbxNode* pNode, FbxAnimLayer* pAnimLayer, void(*DisplayCurve) (FbxAnimCurve* pCurve), void(*DisplayListCurve) (FbxAnimCurve* pCurve, FbxProperty* pProperty), bool isSwitcher, FbxTime lKeyTime);
float testarray(Frame &result, Frame& actual, const FrameBoneNodes& center);
void DisplayAnimation(FbxAnimStack* pAnimStack, FbxNode* pNode, bool isSwitcher = false);
void DisplayAnimation(FbxAudioLayer* pAudioLayer, bool isSwitcher = false);
void CompressAndWriteToFile(FbxString);
void DisplayCurveKeys(FbxAnimCurve* pCurve);
void DisplayListCurveKeys(FbxAnimCurve* pCurve, FbxProperty* pProperty);

void DisplayAnimation(FbxScene* pScene)
{
  int i = 0;

  // Keenan(11)
  pAnimEvaluator = pScene->GetAnimationEvaluator();

	// Keenan(3) - HACK (you'll need to change this later GAM 575 students)
	 for (i = 0; i < pScene->GetSrcObjectCount<FbxAnimStack>(); i++)					//looping through each clip
    {
		 ClipHDR = new ClipHeader();
        FbxAnimStack* lAnimStack = pScene->GetSrcObject<FbxAnimStack>(i);
		
		FbxTimeSpan TimeSpan = lAnimStack->GetLocalTimeSpan();						//time span

		ClipHDR->numofFrames = (int)TimeSpan.GetDuration().GetFrameCount(FbxTime::eFrames30);			//getting the frame count
		// Keenan(11) RAM - RULES good find  <--- He read the manual	
		pScene->SetCurrentAnimationStack(lAnimStack);

        FbxString lOutputString = "Animation Stack Name: ";
        lOutputString += lAnimStack->GetName();
        lOutputString += "\n";
        FBXSDK_printf(lOutputString);
		strcpy_s(ClipHDR->Clipname, lAnimStack->GetName());

        DisplayAnimation(lAnimStack, pScene->GetRootNode());		//called once each clip
		FbxString NameofFile = lAnimStack->GetName();
		NameofFile.Append(".animo",6);
		/////////////////////////////////////
	 	//Lets compress data before writing
		////////////////////////////////////
		CompressAndWriteToFile(NameofFile);







		 
		FrmBcknode.clear();
		FrmBnenode.clear();
    }
}

void DisplayAnimation(FbxAnimStack* pAnimStack, FbxNode* pNode, bool isSwitcher)
{
   
    int nbAnimLayers = pAnimStack->GetMemberCount<FbxAnimLayer>();
    FbxString lOutputString;
	FbxTimeSpan TimeSpan = pAnimStack->GetLocalTimeSpan();

	
     FbxAnimLayer* lAnimLayer = pAnimStack->GetMember<FbxAnimLayer>(0);			//only concerned about zero layers

		  char    lTimeString[256];
		  FbxTime   lKeyTime;
		  int     lCount,numberOfFrames = (int)TimeSpan.GetDuration().GetFrameCount(FbxTime::eFrames30);;

		 

		//going through each of the frames in clip 
		  for (lCount = 0; lCount < numberOfFrames; lCount++)
		  {
			  FrameBucketNodes frmbktnode;
			  frmbktnode.numBones = BoneHDR.Numbones;
			
			  // Keenan(11) - Note this is hard coded... problem for non-30Hz
			  lKeyTime.SetTime(0, 0, 0, lCount, 0, 0, FbxTime::eFrames30);

			  if (isSwitcher == false)
			  {
				  lOutputString = "\n\n ------- Key Time: ";
				  lOutputString += lKeyTime.GetTimeString(lTimeString, FbxUShort(256));
				  int time;
				  sscanf(lTimeString, "%d", &time);
				  frmbktnode.KeyFrameTime = time;
				  FrmBcknode.push_back(frmbktnode);
				  lOutputString += "  ms: ";
				  int msTime = (int)lKeyTime.GetMilliSeconds();
				  
				  lOutputString += msTime;
				  lOutputString += " ------------------ \n\n";
				  printf(lOutputString);
			  }
			  if (isteddy)
				  indexChannels = -1;
			  else
				  indexChannels = -3;

			  DisplayAnimationKeenan(lAnimLayer, pNode, isSwitcher, lKeyTime);
		  }
    


}

// Keenan(8) - api change
void DisplayAnimationKeenan(FbxAnimLayer* pAnimLayer, FbxNode* pNode, bool isSwitcher, FbxTime lKeyTime)
{
	int lModelCount;
	FbxString lOutputString;

	// Keenan(8)
	if (isSwitcher == false)
	{
		lOutputString = "//     Node Name: ";
		lOutputString += pNode->GetName();
		lOutputString += "\n";
		//FBXSDK_printf(lOutputString);
	}
	
	// Keenan(8) add lKeyTime
	if (pNode->GetNodeAttribute() != nullptr &&(
		pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMarker
		||pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh
		||pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eCamera
		||pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eLight

		))
	{
		return;
	}
		DisplayChannelsKeenan(pNode, pAnimLayer, DisplayCurveKeys, DisplayListCurveKeys, isSwitcher, lKeyTime);

		for (lModelCount = 0; lModelCount < pNode->GetChildCount(); lModelCount++)
		{
			// Keenan(8) add lKeyTime
			DisplayAnimationKeenan(pAnimLayer, pNode->GetChild(lModelCount), isSwitcher, lKeyTime);

		}
	
}

#define MATH_PI_180  0.0174532925f

// Keenan(8) - api change
void DisplayChannelsKeenan(FbxNode* pNode, FbxAnimLayer* pAnimLayer, void(*DisplayCurve) (FbxAnimCurve* pCurve), void(*DisplayListCurve) (FbxAnimCurve* pCurve, FbxProperty* pProperty), bool isSwitcher, FbxTime lKeyTime)
{
	FbxAnimCurve* lAnimCurve = NULL;

	char	buff[256];
	FbxString lOutputString;


	// FbxTime::SetGlobalTimeMode ( FbxTime::eFrames30 );
	// Key to the UNIVERSE:  ........ this function
	// FbxAMatrix  matrix = pNode->EvaluateLocalTransform ( lKeyTime );

	// Keenan(10)
	int index = indexChannels;
	indexChannels++;
	FrameBoneNodes currbone;
	// Keenan(11)
	// skip if there are no curves
	lAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
	if(index<0)
	{
		return;
	}
	if (!isSwitcher)		//if not swithcer dont do anything
	{
		FbxAMatrix matrix;
		char    lTimeString[256];
		lKeyTime.GetTimeString(lTimeString, FbxUShort(256));
		int time;
		sscanf(lTimeString, "%d", &time);

		if (!lAnimCurve)		// eval without key frame
		{	
			matrix = pNode->EvaluateLocalTransform();
			if(isteddy)
			{
				currbone.Translation = Vect(0.0f,0.0f,0.0f);
				currbone.Rotation = Quat(ZERO);
				currbone.Scale = Vect(1.0f, 1.0f, 1.0f);
				currbone.boneIndex = index;
				currbone.KeytFrameTime = time;
				FrmBnenode.push_back(currbone);
				return;
			}
			
		}
		else
		{
			matrix = pNode->EvaluateLocalTransform(lKeyTime);
		}
		//we have matrix now push data
		FbxVector4 Trans = matrix.GetT();
		FbxVector4 RotXYZ = matrix.GetR();
		FbxVector4 Scale = matrix.GetS();
		

		currbone.Translation = Vect((float)Trans[0], (float)Trans[1], (float)Trans[2]);
		currbone.Rotation = Quat(ROT_XYZ, RotXYZ[0]*MATH_PI_180, RotXYZ[1] * MATH_PI_180, RotXYZ[2] * MATH_PI_180);
		currbone.Scale = Vect((float)Scale[0], (float)Scale[1], (float)Scale[2]);
		currbone.boneIndex = index;
		currbone.KeytFrameTime = time;
		FrmBnenode.push_back(currbone);
		

	}


	// Display general curves.
	if (!isSwitcher)
	{
		// char    lTimeString[256];

		FbxAMatrix matrix = pNode->EvaluateLocalTransform(lKeyTime);

		// lOutputString = "// Matrix ----- Key Time: ";
		// lOutputString += lKeyTime.GetTimeString(lTimeString, FbxUShort(256));

		//	int timeMS = (int)lKeyTime.GetMilliSeconds();
		//	lOutputString += " timeMS: ";
		//	lOutputString += timeMS;

		//  lOutputString += "\n\n";
		//  printf (lOutputString);

		FbxVector4 Trans = matrix.GetT();
		FbxVector4 RotXYZ = matrix.GetR();
		FbxVector4 Scale = matrix.GetS();

		lOutputString = "pTmp->pBone[";
		lOutputString += index;
		lOutputString += "].T = Vect( ";
		sprintf(buff, "%ff", Trans[0]);
		lOutputString += buff;
		lOutputString += ", ";
		sprintf(buff, "%ff", Trans[1]);
		lOutputString += buff;
		lOutputString += ", ";
		sprintf(buff, "%ff", Trans[2]);
		lOutputString += buff;
		lOutputString += " );\n";
		//printf(lOutputString);

		lOutputString = "pTmp->pBone[";
		lOutputString += index;
		lOutputString += "].Q = Quat( ROT_XYZ,";
		sprintf(buff, "%ff", RotXYZ[0] * MATH_PI_180);
		lOutputString += buff;
		lOutputString += ", ";
		sprintf(buff, "%ff", RotXYZ[1] * MATH_PI_180);
		lOutputString += buff;
		lOutputString += ", ";
		sprintf(buff, "%ff", RotXYZ[2] * MATH_PI_180);
		lOutputString += buff;
		lOutputString += " );\n";
		//printf(lOutputString);

		lOutputString = "pTmp->pBone[";
		lOutputString += index;
		lOutputString += "].S = Vect( ";
		sprintf(buff, "%ff", Scale[0]);
		lOutputString += buff;
		lOutputString += ", ";
		sprintf(buff, "%ff", Scale[1]);
		lOutputString += buff;
		lOutputString += ", ";
		sprintf(buff, "%ff", Scale[2]);
		lOutputString += buff;
		lOutputString += " );\n\n";

		//printf(lOutputString);

	} // if
}


static int InterpolationFlagToIndex(int flags)
{
	if( (flags & FbxAnimCurveDef::eInterpolationConstant) == FbxAnimCurveDef::eInterpolationConstant ) return 1;
    if( (flags & FbxAnimCurveDef::eInterpolationLinear) == FbxAnimCurveDef::eInterpolationLinear ) return 2;
	if( (flags & FbxAnimCurveDef::eInterpolationCubic) == FbxAnimCurveDef::eInterpolationCubic ) return 3;
    return 0;
}

static int ConstantmodeFlagToIndex(int flags)
{
    if( (flags & FbxAnimCurveDef::eConstantStandard) == FbxAnimCurveDef::eConstantStandard ) return 1;
    if( (flags & FbxAnimCurveDef::eConstantNext) == FbxAnimCurveDef::eConstantNext ) return 2;
    return 0;
}

static int TangentmodeFlagToIndex(int flags)
{
    if( (flags & FbxAnimCurveDef::eTangentAuto) == FbxAnimCurveDef::eTangentAuto ) return 1;
    if( (flags & FbxAnimCurveDef::eTangentAutoBreak)== FbxAnimCurveDef::eTangentAutoBreak ) return 2;
    if( (flags & FbxAnimCurveDef::eTangentTCB) == FbxAnimCurveDef::eTangentTCB ) return 3;
    if( (flags & FbxAnimCurveDef::eTangentUser) == FbxAnimCurveDef::eTangentUser ) return 4;
    if( (flags & FbxAnimCurveDef::eTangentGenericBreak) == FbxAnimCurveDef::eTangentGenericBreak ) return 5;
    if( (flags & FbxAnimCurveDef::eTangentBreak) == FbxAnimCurveDef::eTangentBreak ) return 6;
    return 0;
}

static int TangentweightFlagToIndex(int flags)
{
    if( (flags & FbxAnimCurveDef::eWeightedNone) == FbxAnimCurveDef::eWeightedNone ) return 1;
    if( (flags & FbxAnimCurveDef::eWeightedRight) == FbxAnimCurveDef::eWeightedRight ) return 2;
    if( (flags & FbxAnimCurveDef::eWeightedNextLeft) == FbxAnimCurveDef::eWeightedNextLeft ) return 3;
    return 0;
}

static int TangentVelocityFlagToIndex(int flags)
{
    if( (flags & FbxAnimCurveDef::eVelocityNone) == FbxAnimCurveDef::eVelocityNone ) return 1;
    if( (flags & FbxAnimCurveDef::eVelocityRight) == FbxAnimCurveDef::eVelocityRight ) return 2;
    if( (flags & FbxAnimCurveDef::eVelocityNextLeft) == FbxAnimCurveDef::eVelocityNextLeft ) return 3;
    return 0;
}

void DisplayCurveKeys(FbxAnimCurve* pCurve)
{
    static const char* interpolation[] = { "?", "constant", "linear", "cubic"};
    static const char* constantMode[] =  { "?", "Standard", "Next" };
    static const char* cubicMode[] =     { "?", "Auto", "Auto break", "Tcb", "User", "Break", "User break" };
    static const char* tangentWVMode[] = { "?", "None", "Right", "Next left" };

    FbxTime   lKeyTime;
    float   lKeyValue;
    char    lTimeString[256];
    FbxString lOutputString;
    int     lCount;

    int lKeyCount = pCurve->KeyGetCount();
	
	FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);

    for(lCount = 0; lCount < lKeyCount; lCount++)
    {
        lKeyValue = static_cast<float>(pCurve->KeyGetValue(lCount));
        lKeyTime  = pCurve->KeyGetTime(lCount);

        lOutputString = "            Key Time: ";
        lOutputString += lKeyTime.GetTimeString(lTimeString, FbxUShort(256));

		lOutputString += "           In ms: ";
		long long msTime = lKeyTime.GetMilliSeconds();
		lOutputString += (int)msTime;

        lOutputString += ".... Key Value: ";
        lOutputString += lKeyValue;
        lOutputString += " [ ";
        lOutputString += interpolation[ InterpolationFlagToIndex(pCurve->KeyGetInterpolation(lCount)) ];
        if ((pCurve->KeyGetInterpolation(lCount)&FbxAnimCurveDef::eInterpolationConstant) == FbxAnimCurveDef::eInterpolationConstant)
        {
            lOutputString += " | ";
            lOutputString += constantMode[ ConstantmodeFlagToIndex(pCurve->KeyGetConstantMode(lCount)) ];
        }
        else if ((pCurve->KeyGetInterpolation(lCount)&FbxAnimCurveDef::eInterpolationCubic) == FbxAnimCurveDef::eInterpolationCubic)
        {
            lOutputString += " | ";
            lOutputString += cubicMode[ TangentmodeFlagToIndex(pCurve->KeyGetTangentMode(lCount)) ];
            lOutputString += " | ";
			lOutputString += tangentWVMode[ TangentweightFlagToIndex(pCurve->KeyGet(lCount).GetTangentWeightMode()) ];
            lOutputString += " | ";
			lOutputString += tangentWVMode[ TangentVelocityFlagToIndex(pCurve->KeyGet(lCount).GetTangentVelocityMode()) ];
        }
        lOutputString += " ]";
        lOutputString += "\n";
        //FBXSDK_printf (lOutputString);
    }
}

void DisplayListCurveKeys(FbxAnimCurve* pCurve, FbxProperty* pProperty)
{
    FbxTime   lKeyTime;
    int     lKeyValue;
    char    lTimeString[256];
    FbxString lListValue;
    FbxString lOutputString;
    int     lCount;

    int lKeyCount = pCurve->KeyGetCount();

    for(lCount = 0; lCount < lKeyCount; lCount++)
    {
        lKeyValue = static_cast<int>(pCurve->KeyGetValue(lCount));
        lKeyTime  = pCurve->KeyGetTime(lCount);

        lOutputString = "            Key Time: ";
        lOutputString += lKeyTime.GetTimeString(lTimeString, FbxUShort(256));
        lOutputString += ".... Key Value: ";
        lOutputString += lKeyValue;
        lOutputString += " (";
        lOutputString += pProperty->GetEnumValue(lKeyValue);
        lOutputString += ")";

        lOutputString += "\n";
        FBXSDK_printf (lOutputString);
    }
}

void CompressAndWriteToFile(FbxString FileName_)
{
	std::vector<Frame> Clip;
	int count = 0;
 	for (int i =0 ;i<ClipHDR->numofFrames;i++ )		//loops to create the clip object to compress
	{ 
		Frame NewFrame;
		NewFrame.Bucketnode = FrmBcknode[i];
		for (unsigned int j =0; j < NewFrame.Bucketnode.numBones;j++)
		{
			NewFrame.BonesInFrame.push_back(FrmBnenode[count]);
			count++;
		}
		Clip.push_back(NewFrame);
		
	}
	int anchor = 0, candidate=0,conductor;
	float differnece,tS;
	Vect TransResult, ScaleResult;		//todo Change to vaiable
	Quat RotResult;
	Frame ResultFrame;
	ResultFrame.BonesInFrame.resize(80);
	while (anchor < ClipHDR->numofFrames)	//outer most loop till anchor is off the limits
	{//ancor is updated every frames so we should have refreshed loop
		candidate = anchor + 2;
		float error = 0;
		bool iseveythingAcceptable = true;//flag to move anchor forward

		while(iseveythingAcceptable)	//all interpolates are fine keep going forward
		{
			if (candidate < ClipHDR->numofFrames)	//anchor and candidate are valid 
			{
				conductor = anchor + 1;	//Set conductor to second frame
				
				while (conductor<candidate && iseveythingAcceptable)//need to loop and check all the frames in between anchor and candidate
				{	
					
					//need t for conductor frame
					tS = (float)(Clip[conductor].Bucketnode.KeyFrameTime - Clip[anchor].Bucketnode.KeyFrameTime) / (Clip[candidate].Bucketnode.KeyFrameTime - Clip[anchor].Bucketnode.KeyFrameTime);
					bool result = true;
					
					ResultFrame.Bucketnode = Clip[conductor].Bucketnode;
						for (int i = 0; i < Clip[conductor].Bucketnode.numBones && result == true; i++)
						{
						//Lerp slerp lerp
							VectApp::Lerp(ResultFrame.BonesInFrame[i].Translation, Clip[anchor].BonesInFrame[i].Translation, Clip[candidate].BonesInFrame[i].Translation, tS);
							
							QuatApp::Slerp(ResultFrame.BonesInFrame[i].Rotation, Clip[anchor].BonesInFrame[i].Rotation, Clip[candidate].BonesInFrame[i].Rotation, tS);

							VectApp::Lerp(ResultFrame.BonesInFrame[i].Scale, Clip[anchor].BonesInFrame[i].Scale, Clip[candidate].BonesInFrame[i].Scale, tS);
					
						}
						error += testarray(ResultFrame, Clip[conductor], Clip[conductor].BonesInFrame[0]);

						if (error<0.20944f)	//if it is acceptable 
						{
							Clip[conductor].TobeKept = false;
							conductor++;

						}
						else
						{
							iseveythingAcceptable = false;
							//Clip[conductor].TobeKept = true;
							break;
						}
				}
			}
			else
			{
				iseveythingAcceptable = false;
				//edge condition to skip last to frames
				anchor++;
			}\
				if (iseveythingAcceptable)	//everything was good increase the candidate
				{
					candidate++;
				}
				else
				{
					//somethings cant be interpolated you need to understqand that 
					candidate--;
				}
			
		}
		anchor = candidate;
		error = 0.0f;

		
	}
// data is marked for delete
	int reducednumber = 0;
	for (int i = 0; i < ClipHDR->numofFrames; i++)		//loops to create the clip object to compress
	{
		if (Clip[i].TobeKept)
		{
			reducednumber++;
		}

	}
	ClipHDR->numofFrames = reducednumber;
	//Write to file
	File::Handle fh;
	File::Error ferror;
	ferror = File::Open(fh, FileName_, File::WRITE);
	ferror = File::Write(fh, ClipHDR, sizeof(ClipHeader));
	for (size_t i = 0; i < Clip.size(); i++)
	{
		if (Clip[i].TobeKept)
		{
			ferror = File::Write(fh,&Clip[i].Bucketnode, sizeof(FrameBucketNodes));		//writing all frame bucket nodes
		}
	}
	for (size_t i = 0; i < Clip.size(); i++)
	{
		if (Clip[i].TobeKept)
		{
			ferror = File::Write(fh, Clip[i].BonesInFrame.data(), sizeof(FrameBoneNodes)*Clip[i].BonesInFrame.size());		//writing all frame bucket nodes
		}
	}
	ferror = File::Flush(fh);
	ferror = File::Close(fh);



		//Original write to file from fucntion
	//Write to file
	//File::Handle fh;
	//File::Error ferror;
	//ferror = File::Open(fh, FileName_, File::WRITE);
	//ferror = File::Write(fh, ClipHDR, sizeof(ClipHeader));
	//ferror = File::Write(fh, FrmBcknode.data(), sizeof(FrameBucketNodes) * ClipHDR->numofFrames);
	//ferror = File::Write(fh, FrmBnenode.data(), (sizeof(FrameBoneNodes)*FrmBnenode.size()));
	//ferror = File::Flush(fh);
	//ferror = File::Close(fh);
}
float testarray(Frame &result,Frame& actual, const FrameBoneNodes& center)
{
	Vect a, b;

	const Vect Center = center.Translation;
	float error = 0;
	for(unsigned int i = 0; i <result.Bucketnode.numBones;++i)
	{
		a = result.BonesInFrame[i].Translation;
		b = actual.BonesInFrame[i].Translation;
		float iangle, nangle;


		if (a.mag() == 0)
		{
			 iangle = a.dot(Center) / ( Center.mag());
		}
		else
		{
			 iangle = a.dot(Center) / (a.mag() * Center.mag());
		}
		if (b.mag() == 0)
		{
			 nangle = b.dot(Center) / ( Center.mag());
		}
		else
		{
			 nangle = b.dot(Center) / (b.mag() * Center.mag());
		}
		 
		 
		if (iangle > 1.0f)
			iangle = 1.0f;
		if (iangle < -1.0f)
			iangle = -1.0f;

		if (nangle > 1.0f)
			nangle = 1.0f;
		if (nangle < -1.0f)
			nangle = -1.0f;


		const float invcosiangle = acosf(iangle);
		const float invcosnangle = acosf(nangle);

		const float diff = fabs(invcosiangle - invcosnangle);

		error += diff;

	}
	return error;
}
