#include "ModelImporter.h"
#include "PackageHeader.h"
#include "ChunkHeader.h"
#include "ModelManager.h"
#include "File.h"
#include "MathEngine.h"
#include "SkinningModel.h"
#include "SkeletonManager.h"

ModelImporter *ModelImporter::pModelImporter = 0;//forward declaration for static

ModelImporter::ModelImporter()
{
	
}

ModelImporter * ModelImporter::privInstance()
{
	return pModelImporter;
}


void ModelImporter::Create()
{
	privCreate();
}

void ModelImporter::Add(const char * const pModelFileName,Model::Name inModelName,Texture::Name inTextName)
{
	
	File::Handle fh;
	File::Error ferror;
	unsigned int   sizeofspu = GetSize(pModelFileName),VertSize=0,TriSize=0;						//getting size of spu
	ferror = File::Open(fh, pModelFileName, File::READ);		//opening for reading
	unsigned char* pVertsBuff=nullptr,*pTriBuff=nullptr,*pTextureBuff=nullptr;

	if (ferror == File::SUCCESS)
	{
		unsigned char* pMainBuffer = new unsigned char[sizeofspu];	//whole size
		ferror = File::Read(fh, pMainBuffer, sizeofspu);	//read all to buffer
		PackageHeader pkghdr;
		memcpy_s(&pkghdr, sizeof(PackageHeader), pMainBuffer, sizeof(PackageHeader));	//Read package header
		unsigned char* pCursor = pMainBuffer;				//cursor to read through buffer
		pCursor += sizeof(PackageHeader);					//increased to first chunk header
		
		for (unsigned int i = 0; i < pkghdr.numChunks; i++)	//going through all the chunks
		{
			ChunkHeader chkhdr;
			memcpy_s(&chkhdr, sizeof(ChunkHeader), pCursor, sizeof(ChunkHeader));
			pCursor += sizeof(ChunkHeader);
			switch (chkhdr.type)
			{
			case TGA:
			{
				pTextureBuff = new unsigned char[chkhdr.chunkSize];
				memcpy_s(pTextureBuff, chkhdr.chunkSize, pCursor, chkhdr.chunkSize);
				pCursor += chkhdr.chunkSize;
			}
				break;
			case VERTS_TYPE:
			{
				pVertsBuff = new unsigned char[chkhdr.chunkSize];
				VertSize = chkhdr.chunkSize;
				memcpy_s(pVertsBuff, chkhdr.chunkSize, pCursor, chkhdr.chunkSize);
				pCursor += chkhdr.chunkSize;
			}
				break;
			case TRILIST:
			{
				pTriBuff = new unsigned char[chkhdr.chunkSize];
				TriSize = chkhdr.chunkSize;
				memcpy_s(pTriBuff, chkhdr.chunkSize, pCursor, chkhdr.chunkSize);
				pCursor += chkhdr.chunkSize;
			}
				break;
			default:
				assert(FALSE);	//Why are you even here>


				break;


			}
		}//End of loop for each chunk in devi

		ImportedModel *p_model = new ImportedModel(pVertsBuff, pTriBuff, VertSize, TriSize, inModelName);
		p_model->RenderSphere = true;
		ModelManager::Add(p_model);

		Texture::Add(pTextureBuff, inTextName);

	}
}

void ModelImporter::AddSkinedModel(const char * const pskinfile ,Model::Name inName )
{
	
	File::Handle fh;
	File::Error ferror;
	unsigned int   sizeofspu = GetSize(pskinfile);

	ferror = File::Open(fh, pskinfile, File::READ);		//opening for reading
	unsigned char* pMainBuffer = new unsigned char[sizeofspu],*pConductor =pMainBuffer;
	ferror = File::Read(fh, pMainBuffer, sizeofspu);
	SkinHeader sknhdr;
	memcpy(&sknhdr, pMainBuffer, sizeof(SkinHeader));
	pConductor += sizeof(SkinHeader);


	Vert_xyzuvn*pVerts = new Vert_xyzuvn[(unsigned)sknhdr.NumOfVerts ];
	int *BoneIdx = new int[(unsigned)4 * sknhdr.NumOfVerts];
	float *BoneWeight = new float[(unsigned)4 * sknhdr.NumOfVerts];
	int *Trilist = new int[(unsigned)sknhdr.NumOfTris * 3];
	

	memcpy_s(pVerts, (unsigned)sknhdr.NumOfVerts * sizeof(Vert_xyzuvn), pConductor, (unsigned)sknhdr.NumOfVerts * sizeof(Vert_xyzuvn));
	pConductor += sknhdr.NumOfVerts * sizeof(Vert_xyzuvn);
	
	memcpy_s(BoneIdx, (unsigned)sknhdr.NumOfVerts * 16, pConductor, (unsigned)sknhdr.NumOfVerts * 16);		//reading bone indexes
	pConductor += sknhdr.NumOfVerts * 16;

	memcpy_s(BoneWeight, (unsigned)sknhdr.NumOfVerts * 16, pConductor, (unsigned)sknhdr.NumOfVerts * 16);	//reading bone weights
	pConductor += sknhdr.NumOfVerts * 16;

	memcpy_s(Trilist, (unsigned)sknhdr.NumOfTris * 12, pConductor, (unsigned)sknhdr.NumOfTris * 12);

	SkinnedModel *p_skinned_model = new SkinnedModel((unsigned char*)pVerts, (unsigned char*)Trilist, (unsigned char*)BoneIdx, (unsigned char*)BoneWeight, sknhdr.NumOfVerts, sknhdr.NumOfTris, inName);
	ModelManager::Add(p_skinned_model);
	p_skinned_model->isCCW = true;

}

void ModelImporter::privCreate()
{
	if (ModelImporter::pModelImporter == nullptr)
	{
		ModelImporter::pModelImporter = new ModelImporter();
		assert(ModelImporter::pModelImporter);

	}
}

unsigned int ModelImporter::GetSize(const char *const &P)
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