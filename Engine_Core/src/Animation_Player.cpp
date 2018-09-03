#include "Animation_Player.h"
#include "MathEngine.h"
#include "SkeletonManager.h"
#include "ShaderObjectManager.h"
#include "GL/gl3w.h"
#include "Time.h"


//Animation_Player::Animation_Player()
//{
//	this->speed = 0.01f;
//	this->name = Name::NOT_INITIALIZED;
//	this->pActiveClip = nullptr;
//	this->pClipHead = nullptr;
//	this->pNext = nullptr;
//	this->pPrev = nullptr;
//
//	this->tcurrent = Time(Time::ZERO);
//}

Animation_Player::Animation_Player(Skeleton::Name inSkelName_, Animation_Player::Name inName_,bool GpuAnimation)
{
	this->speed = 0.05f;			// can varry to speed or decrease the speed
	this->name = inName_;
	this->pSkeleton = SkeletonManager::Find(inSkelName_); 
	this->pNext = nullptr;
	this->pPrev = nullptr;
	this->pActiveClip = nullptr;
	this->pClipHead = nullptr;
	this->tcurrent = Time(Time::ZERO);
	this->gpuAnimation = GpuAnimation;

	//
	//this->pTestBufferIn = new ShaderBufferObject();
	//this->pTestBufferOut = new ShaderBufferObject();
	this->pFrameA_ssbo = new ShaderBufferObject();
	this->pFrameB_ssbo = new ShaderBufferObject();
	this->plocalmatrix_ssbo = new ShaderBufferObject();
	this->pBit_ssbo = new ShaderBufferObject();

	//initialize the result buffers
	//comp1
	ShaderBufferObject::Desc Info;
	Info.numberofElements = (unsigned int)pSkeleton->numbones;
	Info.StructureSize = sizeof(Vect) + sizeof(Vect) + sizeof(Quat);// +sizeof(Quat) + sizeof(Vect);
	float *data = new float[Info.numberofElements*Info.StructureSize];
	Info.pData = data;
	this->plocalmatrix_ssbo->PushDataToGpu(Info);
	//this->plocalmatrix_ssbo->MapData(ShaderBufferObject::READ_ONLY);
	delete[] data;
	//comp2
	Info.StructureSize = sizeof(Matrix);
	Info.numberofElements = (unsigned int)pSkeleton->numbones;
	Matrix *pFiller = new Matrix[(unsigned int)pSkeleton->numbones];
	Info.pData = pFiller;
	this->pBit_ssbo->PushDataToGpu(Info);
	delete[] pFiller;
}

Animation_Player::~Animation_Player()
{
	delete this->pBit_ssbo;
	delete this->pFrameA_ssbo;
	delete this->pFrameB_ssbo;
	delete this->plocalmatrix_ssbo;
	Clip *pConductor = this->pClipHead;
	while(pConductor!= nullptr)
	{
		Clip *pToBeDelete;
		pToBeDelete = pConductor;
		pConductor = pConductor->PNext;
		delete pToBeDelete;
	}
}

void Animation_Player::ProcessAnimation()
{
	//Trace::out("time:%f\n", tCurr / Time(Time::ONE_SECOND));

	Frame_Bucket *pTmp = pActiveClip->PheadBucket->nextBucket;

	

	// First one is the result, skip it
	pTmp = pActiveClip->PheadBucket->nextBucket;

	// Find which key frames
	while (tcurrent >= pTmp->KeyTime  && pTmp->nextBucket != 0)
	{
		pTmp = pTmp->nextBucket;
	}

	// pTmp is the "B" key frame
	// pTmp->prev is the "A" key frame
	Frame_Bucket *pA = pTmp->prevBucket;
	Frame_Bucket *pB = pTmp;

	// find the "S" of the time
	float tS = (tcurrent - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

	

	if(this->gpuAnimation)
	{
		//gpu
		privProcessGPUanim( pA,pB, tS);
	}
	else
	{
		//old things
		privProcessCPUanim( pA, pB, tS);
	}
}

void Animation_Player::PushDataToSkeleton()
{
	for(int i = 0; i < pSkeleton->getBonesNum();i++)
	{
		 pSkeleton->pResult[i] = this->pActiveClip->PheadBucket->pBone[i];
	}
}

void Animation_Player::SetSpeed(float inspeed)
{
	this->speed = inspeed;
}

float Animation_Player::GetSpeed(void)
{
	return this->speed;
}

void Animation_Player::Update()
{
	Time deltaTime = speed* Time(Time::NTSC_30_FRAME);
	Time maxTime;

	tcurrent += deltaTime;

	FindMaxTime(maxTime);

	// protection for time values for looping
	if (tcurrent < Time(Time::ZERO))
	{
		tcurrent = maxTime;
	}
	else if (tcurrent > maxTime)
	{
		tcurrent = Time(Time::ZERO);
	}
	else
	{
		// do nothing
	}

	ProcessAnimation();
	
	
	//PushDataToSkeleton();




}

void Animation_Player::privProcessGPUanim(Frame_Bucket * pA, Frame_Bucket * pB, float t_)
{
	//t is lerp factor
	////////////////////////
		//Computer Shader 1
	/////////////////////////
	//Get shader
	ShaderObject *pCompShader1 = ShaderObjectManager::Find(ShaderObject::Name::COMP_Interpolate);
	pCompShader1->SetActive();
	
	//push uniforms
	glUniform1f(pCompShader1->GetLocation("lerpFactor"), t_);							// lerp factor
	glUniform1i(pCompShader1->GetLocation("numBones"), pSkeleton->numbones);		//one for the rigidbones

	// push uniform of rigidbone may be latter wil lsee.

//push data for frame 1 and frame2

	ShaderBufferObject::Desc Info;
	Info.StructureSize = sizeof(Vect) + sizeof(Vect) + sizeof(Quat);
	Info.numberofElements = (unsigned int)pSkeleton->numbones;
	Info.pData = pA->pBone;

	//descriptor ready.. now push
	this->pFrameA_ssbo->PushDataToGpu(Info);
	this->pFrameA_ssbo->BindLayout(0);
	//Bone*b = (Bone*)this->pFrameA_ssbo->MapData(ShaderBufferObject::READ_ONLY);
	//only pdaata changes
	Info.pData = pB->pBone;
	this->pFrameB_ssbo->PushDataToGpu(Info);
	this->pFrameB_ssbo->BindLayout(1);
	this->plocalmatrix_ssbo->BindLayout(2);
	unsigned int globalGroupCount = (unsigned int)ceilf((float)Info.numberofElements / (float)LOCAL_COMPUTE_THREAD_COUNT);

	pCompShader1->Dispatch(globalGroupCount, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	
//test for working
#if 0		// test for workign ssbo and map
ShaderBufferObject::Desc inputInfo;

const unsigned int testBufferSize = 100;

unsigned int input[testBufferSize];
for (unsigned int i = 0; i < testBufferSize; i++)
{
	input[i] = i;
}
inputInfo.numberofElements = testBufferSize;
inputInfo.StructureSize = sizeof(int);
inputInfo.pData = &input;
this->pTestBufferIn->PushDataToGpu(inputInfo);

this->pTestBufferOut->PushDataToGpu(inputInfo);
ShaderObject * pCompShader = ShaderObjectManager::Find(ShaderObject::Name::COMP_TEST);

unsigned int globalGroupCount = (unsigned int)ceilf((float)testBufferSize / (float)LOCAL_COMPUTE_THREAD_COUNT);

pTestBufferIn->BindLayout(0);
pTestBufferOut->BindLayout(1);

pCompShader->SetActive();
pCompShader->Dispatch(globalGroupCount, 1, 1);
glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

int * pResult = reinterpret_cast<int*>(pTestBufferOut->MapData(ShaderBufferObject::Access::READ_ONLY));

for (auto i = 0; i < testBufferSize; ++i)
{
	assert(pResult[i] == i + 1);
}

pTestBufferOut->UnMapData();
#endif

ShaderObject*pCompShader2 = ShaderObjectManager::Find(ShaderObject::COMP_localtoworld);
pCompShader2->SetActive();

//push uinforms
this->pSkeleton->pRigid->Update(Time(Time::ONE_MILLISECOND));
Matrix RigidWorldmat = this->pSkeleton->pRigid->GetWorld();
glUniform1i(pCompShader2->GetLocation("maxHierarchyDepth"),this->pSkeleton->maxDepth); // depth + 1 to account for rigid game object
glUniform1i(pCompShader2->GetLocation("numBones"), this->pSkeleton->numbones);	//numBones + 1 to account for rigid game object
glUniformMatrix4fv(pCompShader2->GetLocation("Rigidworld_matrix"),1,GL_FALSE,(float*)&RigidWorldmat);

//sety ssbo
this->plocalmatrix_ssbo->BindLayout(0);
this->pSkeleton->pHeirarchyssbo->BindLayout(1);
this->pSkeleton->pInversessbo->BindLayout(2);
this->pBit_ssbo->BindLayout(3);

//runn th shdaer
pCompShader2->Dispatch(globalGroupCount, 1, 1);

glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);


}

void Animation_Player::privProcessCPUanim(Frame_Bucket * pA, Frame_Bucket * pB, float t_)
{
#if 0
	// Get the result bone array
	// Remember the firs Frame is the result
	Bone *bResult = pActiveClip->PheadBucket->pBone;
	// interpolate to 
	Bone *bA = pA->pBone;
	Bone *bB = pB->pBone;

	// Interpolate to tS time, for all bones
	for (int i = 0; i < this->pSkeleton->getBonesNum(); i++)
	{
		// interpolate ahoy!
		VectApp::Lerp(bResult->T, bA->T, bB->T, t_);
		QuatApp::Slerp(bResult->Q, bA->Q, bB->Q, t_);
		VectApp::Lerp(bResult->S, bA->S, bB->S, t_);

		// advance the pointer
		bA++;
		bB++;
		bResult++;
	}
#endif


#if 1

	privProcessGPUanim(pA, pB, t_);

	/*Bone*b = (Bone*)this->plocalmatrix_ssbo->MapData(ShaderBufferObject::READ_ONLY);
	      
	memcpy_s(this->pActiveClip->PheadBucket->pBone, this->pSkeleton->numbones * sizeof(Bone), b, this->pSkeleton->numbones * sizeof(Bone));

	this->plocalmatrix_ssbo->UnMapData();

	Matrix *peval = (Matrix*)this->pBit_ssbo->MapData(ShaderBufferObject::READ_ONLY);

	memcpy_s(this->pSkeleton->pWorldOfBones, this->pSkeleton->numbones * sizeof(Matrix),peval, this->pSkeleton->numbones * sizeof(Matrix));

	this->pBit_ssbo->UnMapData();*/

#endif


}

void Animation_Player::increaseSpeed()
{
	this->speed = 0.03f;
}

void Animation_Player::decreaseSpeed()
{
	if(this->speed> 0.0f)
	{
		this->speed -= 0.01f;
	}
}

void Animation_Player::AddClip(Clip * inClip)
{
	if(this->pClipHead == 0)
	{
		pClipHead = inClip;
		inClip->PNext = nullptr;
		inClip->pPrev = nullptr;
	}
	else
	{
		inClip->PNext = pClipHead; 
		pClipHead->pPrev = inClip;
		pClipHead = inClip;

	}
}

void Animation_Player::FindMaxTime(Time & tMax)
{
	Frame_Bucket *pTmp = this->pActiveClip->PheadBucket->nextBucket;

	while (pTmp->nextBucket != 0)
	{
		pTmp = pTmp->nextBucket;
	}

	tMax = pTmp->KeyTime;
}
