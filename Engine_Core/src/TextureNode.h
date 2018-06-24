#ifndef TEXTURE_NODE_H
#define TEXTURE_NODE_H

#include "Texture.h"
#include "TextureNodeLink.h"

class TextureNode: public TextureNodeLink
{
public:
	TextureNode();
	void set( const char * const _assetName, 
				Texture::Name _name, 
				GLuint _TextureID, 
				GLenum minFilter, 
				GLenum magFilter, 
		GLenum horizWrapMode,
		GLenum vertwrapMode );

private:
	char assetName[Texture::ASSET_NAME_SIZE];

public:
	Texture::Name name;
	GLuint textureID;
	GLenum minFilter;
	GLenum magFilter;
	GLenum horizWrapMode;
	GLenum vertwrapMode;
	int RefCount;
};



#endif