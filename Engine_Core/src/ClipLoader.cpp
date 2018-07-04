#include "ClipLoader.h"
#include "File.h"
#include "Structs.h"

ClipLoader* ClipLoader::pClipImporter;

void ClipLoader::Create()
{
	privCreate();
}

Clip* ClipLoader::Add(const char * const pModelFileName, Clip::Name inname)
{
	File::Handle fh;
	File::Error ferror;
	ferror = File::Open(fh, pModelFileName, File::READ);		//opening for reading
	assert(ferror == File::SUCCESS);
	unsigned int   sizeoffile = GetSize(pModelFileName);						//getting size of spu
	unsigned char* pMainBuffer = new unsigned char[sizeoffile];	//whole size
	ferror = File::Read(fh, pMainBuffer, sizeoffile);	//read all to buffer
	assert(ferror == File::SUCCESS);
	ClipHeader clphdr;
	
	memcpy_s(&clphdr, sizeof(ClipHeader), pMainBuffer, sizeof(ClipHeader));
	unsigned char* pCursor = pMainBuffer;				//cursor to read through buffer
	pCursor += sizeof(ClipHeader);

	//read all framebucket 
	FrameBucketNodes *pFrmNde = new FrameBucketNodes[(unsigned)clphdr.numofFrames]();
	memcpy_s(pFrmNde, (sizeof(FrameBucketNodes)*clphdr.numofFrames), pCursor, sizeof(FrameBucketNodes)*clphdr.numofFrames);
	pCursor += (sizeof(FrameBucketNodes)*clphdr.numofFrames);
	FrameBoneNodes* pfrmbnende = new FrameBoneNodes[(clphdr.numofFrames*pFrmNde->numBones)]();
	memcpy_s(pfrmbnende, (sizeof(FrameBoneNodes)*(clphdr.numofFrames*pFrmNde->numBones)), pCursor, sizeof(FrameBoneNodes)*(clphdr.numofFrames*pFrmNde->numBones));
	//create clip
	Clip *pClip = new Clip(inname);
	//create presult frame
	pClip->PheadBucket = new Frame_Bucket();
	pClip->PheadBucket->prevBucket = 0;
	pClip->PheadBucket->nextBucket = 0;
	pClip->PheadBucket->pBone = new Bone[pFrmNde->numBones];
	pClip->PheadBucket->KeyTime = Time(Time::ZERO);

	//Fill the frame buckets now
	Frame_Bucket *PrevBuck = pClip->PheadBucket;
	for(int currFram=0;currFram<clphdr.numofFrames;currFram++)
	{
		Frame_Bucket *p_frame_bucket = new Frame_Bucket();
		p_frame_bucket->pBone = new Bone[pFrmNde->numBones];
		p_frame_bucket->KeyTime = pFrmNde->KeyFrameTime*Time(Time::NTSC_30_FRAME);
		p_frame_bucket->prevBucket = PrevBuck;
		p_frame_bucket->nextBucket = 0;
				//fill the bones
				for(unsigned int i=0;i<pFrmNde->numBones;i++)
				{
					if (pfrmbnende->boneIndex == (signed)i && p_frame_bucket->KeyTime == pfrmbnende->KeytFrameTime*Time(Time::NTSC_30_FRAME))
					{
						p_frame_bucket->pBone[i].Q = pfrmbnende->Rotation;
						p_frame_bucket->pBone[i].S = pfrmbnende->Scale;
						p_frame_bucket->pBone[i].T = pfrmbnende->Translation;
						pfrmbnende++;
					}
					
				}




		
		PrevBuck->nextBucket = p_frame_bucket;
		PrevBuck = p_frame_bucket;
		pFrmNde++;
		
	}
	//delete[] pfrmbnende;
	//delete[] pFrmNde;

	return pClip;
	
}

ClipLoader::ClipLoader()
{
}

ClipLoader * ClipLoader::privInstance()
{
	return pClipImporter;
}

void ClipLoader::privCreate()
{
	if (ClipLoader::pClipImporter == nullptr)
	{
		ClipLoader::pClipImporter = new ClipLoader();
		assert(ClipLoader::pClipImporter);

	}
}

unsigned int ClipLoader::GetSize(const char * const & P)
{
	unsigned int size = 0;

	File::Handle f_handle;
	File::Error ferror;
	ferror = File::Open(f_handle, P, File::Mode::READ);

	if (ferror == File::SUCCESS)
	{
		ferror = File::Seek(f_handle, File::Location::END, 0);	//Go To End see the whole size
		ferror = File::Tell(f_handle, size);		// size saved in size
		ferror = File::Seek(f_handle, File::Location::BEGIN, 0);	//Go To Begin and lets read the data;
		ferror = File::Close(f_handle);		// close as not required anymore

	}
	return size;
}


