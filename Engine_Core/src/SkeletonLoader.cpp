#include "SkeletonLoader.h"
#include "GameObjectManager.h"
#include "GraphicsObject_PointLight.h"
#include "GameObjectRigid.h"
#include "ShaderObjectManager.h"
#include "ModelManager.h"
#include "GraphicsObject_Null.h"
#include "Structs.h"
#include "SkeletonManager.h"
#include "Trace.h"
#include "Matrix.h"

SkeletonLoader * SkeletonLoader::pSkeletonImporter;

void SkeletonLoader::Create()
{
	privCreate();
}

void SkeletonLoader::Add(const char * const pModelFileName,float size, const char * const pInverse,Skeleton::Name inname)
{

	File::Handle fh;
	File::Error ferror;
	ferror = File::Open(fh, pModelFileName, File::READ);		//opening for reading
	unsigned int   sizeoffile = GetSize(pModelFileName);						//getting size of spu
	unsigned char* pMainBuffer = new unsigned char[sizeoffile];	//whole size
	ferror = File::Read(fh, pMainBuffer, sizeoffile);	//read all to buffer
	ferror = File::Close(fh);
	BoneHeader bnehdr;
	memcpy_s(&bnehdr, sizeof(BoneHeader), pMainBuffer, sizeof(BoneHeader));
	unsigned char* pCursor = pMainBuffer;				//cursor to read through buffer
	pCursor += sizeof(BoneHeader);

	//pcursor is at pci list
	ParentChildIndex *pcilist = new ParentChildIndex[(unsigned)bnehdr.Numbones]();
	memcpy_s(pcilist, (sizeof(ParentChildIndex)*bnehdr.Numbones), pCursor, sizeof(ParentChildIndex)*bnehdr.Numbones);
	pCursor += sizeof(ParentChildIndex)*bnehdr.Numbones;
	//int array for table??>????
	int *tabledata = new int[(unsigned int)bnehdr.Numbones*bnehdr.MaxDepth];
	memcpy_s(tabledata, (sizeof(int)*(bnehdr.Numbones*bnehdr.MaxDepth)), pCursor,(sizeof(int)*(bnehdr.Numbones*bnehdr.MaxDepth)));



	Skeleton *p_skeleton = new Skeleton(bnehdr.Numbones,inname);
	p_skeleton->maxDepth = bnehdr.MaxDepth;

	Vect color;
	Vect pos(1, 1, 1);
	color.set(1.0f, 1.0f, 1.0f, 1.0f);
	GraphicsObject_PointLight *pGraphics_TextureLight;
	pGraphics_TextureLight = new GraphicsObject_PointLight(ModelManager::Find(Model::Pyramid), ShaderObjectManager::Find(ShaderObject::POINTLIGHT_TEXTURE), Texture::Name::DUCKWEED, color, pos, GraphicsObject::Name::PYRAMID_POINTLIGHT_duck);

	// Create GameObject
	

	//PCSTree *pTree = GameObjectManager::GetTree();
	
	GraphicsObject_Null *pnullgraphicc = new GraphicsObject_Null(ModelManager::Find(Model::Null_Object), ShaderObjectManager::Find(ShaderObject::NULL_SHADER));
	p_skeleton->pRigid = new GameObjectRigid(pnullgraphicc);
	
	p_skeleton->pRigid->setScale(Vect(size, size, size));
	p_skeleton->pRigid->setPos(Vect(0.0f, 0.0f, 0.0f));
	GameObjectManager::Add(p_skeleton->pRigid, GameObjectManager::GetRoot());
	
	//load skelton
	//For first BONE_WIDTH
	int i = 0;
	GameObjectAnim *pBip01 = new GameObjectAnim(pGraphics_TextureLight);
	pBip01->SetIndex(pcilist[i].myIndex);
	pBip01->SetName(pcilist[i].NodeName);
	pBip01->Pskeleton = p_skeleton;
	GameObjectManager::Add(pBip01, p_skeleton->pRigid);
	p_skeleton->pRoot = pBip01;
	i++;
	for( ;i<bnehdr.Numbones;i++)
	{
		GameObjectAnim *pGOBA = new GameObjectAnim(pGraphics_TextureLight);
		pGOBA->SetIndex(pcilist[i].myIndex);
		pGOBA->SetName(pcilist[i].NodeName);
		pGOBA->Pskeleton = p_skeleton;

		GameObjectAnim *pGOBP =(GameObjectAnim*) GameObjectManager::Find(pBip01, pcilist[i].parentIndex);
		GameObjectManager::Add(pGOBA, pGOBP);
	}
	//adding inverse before the getting out

	File::Handle fh2;
	File::Error ferror2;
	unsigned int sizeofspu = GetSize(pInverse);
	ferror2 = File::Open(fh2, pInverse, File::READ);		//opening for reading boneinverses
	unsigned char* pMainBuffer2 = new unsigned char[sizeofspu], *pConductor2 = pMainBuffer2;
	ferror2 = File::Read(fh2, pMainBuffer2, sizeofspu);
	ferror2 = File::Close(fh2);
	BoneHeader BneHdr;
	memcpy(&BneHdr, pMainBuffer2, sizeof(BoneHeader));
	pConductor2 += sizeof(BoneHeader);
	Matrix *inverseWorld = new Matrix[(unsigned)BneHdr.Numbones];
	memcpy(inverseWorld, pConductor2, sizeof(Matrix)*BneHdr.Numbones);

	p_skeleton->pPoseInverse = inverseWorld;

	ShaderBufferObject::Desc Info;
	Info.numberofElements =(unsigned int)bnehdr.Numbones*bnehdr.MaxDepth;
	Info.StructureSize = sizeof(unsigned int);
	Info.pData = tabledata;
	
	//push data to the ssbio
	p_skeleton->pHeirarchyssbo->PushDataToGpu(Info);
	//check it
#if 0

	int *pCheckdata = (int*)p_skeleton->pHeirarchyssbo->MapData(ShaderBufferObject::Access::READ_ONLY);
	for ( i = 0; i < bnehdr.Numbones; i++)
	{
		for (auto j = 0; j < bnehdr.MaxDepth; j++)
		{
			Trace::out(" %d",pCheckdata[i * bnehdr.MaxDepth+ j]);
		}
		Trace::out("\n");
	}

	Trace::out("\n \n");
	p_skeleton->pHeirarchyssbo->UnMapData();

#endif // 0
	 //nowpush the bone inverse
	Info.StructureSize = sizeof(Matrix);
	Info.numberofElements = (unsigned int)BneHdr.Numbones;
	Info.pData = p_skeleton->pPoseInverse;

	p_skeleton->pInversessbo->PushDataToGpu(Info);
#if 0

	Matrix *pCheckdata = (Matrix*)p_skeleton->pInversessbo->MapData(ShaderBufferObject::Access::READ_ONLY);
	for (i = 0; i < bnehdr.Numbones; i++)
	{
		assert(pCheckdata[i][m0] == p_skeleton->pPoseInverse[i][m0]);
		assert(pCheckdata[i][m1] == p_skeleton->pPoseInverse[i][m1]);
		assert(pCheckdata[i][m2] == p_skeleton->pPoseInverse[i][m2]);
		assert(pCheckdata[i][m3] == p_skeleton->pPoseInverse[i][m3]);
		assert(pCheckdata[i][m4] == p_skeleton->pPoseInverse[i][m4]);
		assert(pCheckdata[i][m5] == p_skeleton->pPoseInverse[i][m5]);
		assert(pCheckdata[i][m6] == p_skeleton->pPoseInverse[i][m6]);
		assert(pCheckdata[i][m7] == p_skeleton->pPoseInverse[i][m7]);
		assert(pCheckdata[i][m8] == p_skeleton->pPoseInverse[i][m8]);
		assert(pCheckdata[i][m9] == p_skeleton->pPoseInverse[i][m9]);
		assert(pCheckdata[i][m10]== p_skeleton->pPoseInverse[i][m10]);
		assert(pCheckdata[i][m11] == p_skeleton->pPoseInverse[i][m11]);
		assert(pCheckdata[i][m12] == p_skeleton->pPoseInverse[i][m12]);
		assert(pCheckdata[i][m13] == p_skeleton->pPoseInverse[i][m13]);
		assert(pCheckdata[i][m14] == p_skeleton->pPoseInverse[i][m14]);
		assert(pCheckdata[i][m15] == p_skeleton->pPoseInverse[i][m15]);

	}

	Trace::out("\n \n");
	p_skeleton->pInversessbo->UnMapData();

#endif // 0



	SkeletonManager::Add(p_skeleton);
}

SkeletonLoader::SkeletonLoader()
{
}

SkeletonLoader * SkeletonLoader::privInstance()
{
	return pSkeletonImporter;
}

void SkeletonLoader::privCreate()
{
	if (SkeletonLoader::pSkeletonImporter == nullptr)
	{
		SkeletonLoader::pSkeletonImporter = new SkeletonLoader();
		assert(SkeletonLoader::pSkeletonImporter);

	}
}

unsigned int SkeletonLoader::GetSize(const char * const & P)
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



