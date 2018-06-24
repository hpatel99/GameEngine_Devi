#include "TextureNode.h"
#include "ShaderObject.h"

TextureNode::TextureNode()
	:name(Texture::Name::NOT_INITIALIZED),
	textureID(0),
	minFilter(GL_LINEAR),
	magFilter(GL_LINEAR),
	horizWrapMode(GL_CLAMP_TO_EDGE),
	vertwrapMode(GL_CLAMP_TO_EDGE),
	RefCount(0)
{
	memset(this->assetName, 0, Texture::ASSET_NAME_SIZE);

}

void TextureNode::set(const char * const _assetName, 
	Texture::Name _name, 
	GLuint _TextureID, 
	GLenum _minFilter, 
	GLenum _magFilter, 
	GLenum _horizWrapMode,
	GLenum _vertWrapMode)
{
	memset(this->assetName, 0x0, Texture::ASSET_NAME_SIZE);
	memcpy(this->assetName, _assetName, Texture::ASSET_NAME_SIZE - 1);
	this->name = _name;
	this->magFilter = _magFilter;
	this->minFilter = _minFilter;
	this->horizWrapMode = _horizWrapMode;
	this->vertwrapMode = _vertWrapMode;
	this->textureID = _TextureID;
}
