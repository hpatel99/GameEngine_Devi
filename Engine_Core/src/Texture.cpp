#include <sb7.h>
#include <stdlib.h>
#include <assert.h>

#include "TGA.h"
#include "Texture.h"
#include "TextureNode.h"

Texture::Texture()
{
	this->active = nullptr;
}
Texture* Texture::privGetInstance()
{
	static Texture textMan;
	return &textMan;
}
void Texture::Add(const char* const _assetName, const Texture::Name _name)
{
	GLuint               textureID;
	GLuint *pTextureID = &textureID;

	// Get the instance to the manager
	Texture *pTextMan = Texture::privGetInstance();

	// Load the texture and get the textureID
	pTextMan->privLoadTexture(_assetName, pTextureID);

	// Create a TextureNode
	TextureNode *pNode = new TextureNode();

	// initialize it
	pNode->set(_assetName, _name, textureID, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	// Now add it to the manager
	pTextMan->privAddToFront(pNode, pTextMan->active);
}

void Texture::Add(unsigned char * _buffer, const Texture::Name _name)
{
	GLuint               textureID;
	GLuint *pTextureID = &textureID;

	// Get the instance to the manager
	Texture *pTextMan = Texture::privGetInstance();

	// Load the texture and get the textureID
	pTextMan->privLoadTexture(_buffer, pTextureID);

	// Create a TextureNode
	TextureNode *pNode = new TextureNode();

	// initialize it
	pNode->set("importedtexture", _name, textureID, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	// Now add it to the manager
	pTextMan->privAddToFront(pNode, pTextMan->active);
}

GLuint Texture::Find(const Texture::Name _name)
{
	// Get the instance to the manager
	Texture *pTextMan = Texture::privGetInstance();

	TextureNode *pNode = (TextureNode *)pTextMan->active;
	while (pNode != 0)
	{
		if (pNode->name == _name)
		{
			// found it
			break;
		}

		pNode = (TextureNode *)pNode->next;
	}

	return pNode->textureID;
}


void Texture::DeleteAllTextures()
{
	// Get the instance to the manager
	Texture *pTextMan = Texture::privGetInstance();

	TextureNode *pNode = (TextureNode *)pTextMan->active;
	while (pNode != 0)
	{
		// bye bye
		glDeleteTextures(1, &pNode->textureID);

		// next
		pNode = (TextureNode *)pNode->next;
	}
}

void Texture::privAddToFront(TextureNodeLink *node, TextureNodeLink *&head)
{
	assert(node != 0);

	if (head == 0)
	{
		head = node;
		node->next = 0;
		node->prev = 0;
	}
	else
	{
		node->next = head;
		head->prev = node;
		head = node;
	}
}

void Texture::privLoadTexture(const char * const _assetName, GLuint *&textureID)
{
	// Get an ID, for textures (OpenGL poor man's handle)
	glGenTextures(1, textureID);

	// Bind it.
	glBindTexture(GL_TEXTURE_2D, *textureID);

	// Loat the texture
	this->privLoadTGATexture(_assetName, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE);
}

void Texture::privLoadTexture(unsigned char * const _buffer, GLuint *& textureID)
{// Get an ID, for textures (OpenGL poor man's handle)
	glGenTextures(1, textureID);

	// Bind it.
	glBindTexture(GL_TEXTURE_2D, *textureID);

	// Loat the texture
	this->privLoadTGATexture(_buffer, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

// Load a TGA as a 2D Texture. Completely initialize the state
bool Texture::privLoadTGATexture(const char* szFileName, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;

	// Read the texture bits
	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	if (pBits == NULL)
		return false;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)horizWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)vertWrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

	free(pBits);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return true;
}

bool Texture::privLoadTGATexture(unsigned char * _buffer, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;

	// Read the texture bits
	pBits = gltReadTGABits(_buffer, &nWidth, &nHeight, &nComponents, &eFormat);
	if (pBits == NULL)
		return false;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)horizWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)vertWrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBits);

	free(pBits);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return true;
}




////////////////////////////////////////////////////////////////////
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
GLbyte *Texture::gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits

									// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_RGB;
	*iComponents = GL_RGB;

	// Attempt to open the file
	fopen_s(&pFile, szFileName, "rb");
	if (pFile == NULL)
		return NULL;

	// Read in header (binary)
	fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);


	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = (unsigned int)tgaHeader.width *  (unsigned int)tgaHeader.height *  (unsigned int)sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{

	case 3:     // Most likely case
		*eFormat = GL_BGR;
		*iComponents = GL_RGB;
		break;

	case 4:
		*eFormat = GL_BGRA;
		*iComponents = GL_RGBA;
		break;
	case 1:
		assert(false);
		// bad case - keenan
		// i commented out
		//  *eFormat = GL_LUMINANCE;
		//  *iComponents = GL_LUMINANCE;
		break;
	default:        // RGB
					// If on the iPhone, TGA's are BGR, and the iPhone does not 
					// support BGR without alpha, but it does support RGB,
					// so a simple swizzle of the red and blue bytes will suffice.
					// For faster iPhone loads however, save your TGA's with an Alpha!

		break;
	}



	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}

GLbyte * Texture::gltReadTGABits(unsigned char * _buffer, GLint * iWidth, GLint * iHeight, GLint * iComponents, GLenum * eFormat)
{
	unsigned char * pConductor = _buffer;		// to move as we read the data
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits

									// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_RGB;
	*iComponents = GL_RGB;

	
	// Read in header (binary)
	//fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);
	memcpy_s(&tgaHeader, 18, pConductor, 18);
	pConductor += 18;


	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = (unsigned int)tgaHeader.width *  (unsigned int)tgaHeader.height *  (unsigned int)sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	/*if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}*/
	memcpy_s(pBits, lImageSize, pConductor, lImageSize);
	// Set OpenGL format expected
	switch (sDepth)
	{

	case 3:     // Most likely case
		*eFormat = GL_BGR;
		*iComponents = GL_RGB;
		break;

	case 4:
		*eFormat = GL_BGRA;
		*iComponents = GL_RGBA;
		break;
	case 1:
		assert(false);
		// bad case - keenan
		// i commented out
		//  *eFormat = GL_LUMINANCE;
		//  *iComponents = GL_LUMINANCE;
		break;
	default:        // RGB
					// If on the iPhone, TGA's are BGR, and the iPhone does not 
					// support BGR without alpha, but it does support RGB,
					// so a simple swizzle of the red and blue bytes will suffice.
					// For faster iPhone loads however, save your TGA's with an Alpha!

		break;
	}



	// Done with File
	/*fclose(pFile);*/

	// Return pointer to image data
	return pBits;
}
