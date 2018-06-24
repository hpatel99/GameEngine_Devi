#ifndef MODEL_FILE_HEADER_H
#define MODEL_FILE_HEADER_H

#include <string.h>

#define OBJECT_NAME_SIZE   32
#define TEXTURE_NAME_SIZE  32

struct ModelFileHeader
{
	// object name
	char         objName[OBJECT_NAME_SIZE];

	// vertex buffer
	int          numVerts;
	unsigned int vertBufferOffset;

	// trilist index 
	int          numTriList;
	unsigned int triListBufferOffset;

	// texture info
	//char         textName[TEXTURE_NAME_SIZE];
	//unsigned int textMinFilter;
	//unsigned int textMagFilter;
	//unsigned int textWrapMode;

	ModelFileHeader()
	{
		memset(this, 0x0, sizeof(ModelFileHeader));
	}
};


#endif