#ifndef SHADER_BUFFER_OBJ
#define SHADER_BUFFER_OBJ
#include <sb7.h>
class ShaderBufferObject
{
	
public :
	enum Access
	{//to match with opengl
		READ_ONLY = 0x88B8,
		WRITE_ONLY = 0x88B9,
		READ_WRITE = 0x88BA

	};
	struct Desc
	{
		Desc() :numberofElements(0),StructureSize(0),pData(0){};
		unsigned int numberofElements;
		unsigned int StructureSize;
		void *pData;
		Desc(unsigned int NumOfElement,unsigned int StructureSize,void* InData_)
		{
			this->numberofElements = NumOfElement;
			this->StructureSize = StructureSize;
			this->pData = InData_;
		}
	};


	ShaderBufferObject();
	~ShaderBufferObject();

	void PushDataToGpu(Desc inDesc_);
	void BindLayout(unsigned int LayoutID_);
	void UnBind();
	unsigned int GetID()const;

	void * MapData(Access access);

	void UnMapData();

	//data
	unsigned int ID;
};
#endif
