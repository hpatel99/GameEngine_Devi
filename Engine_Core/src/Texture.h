#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "sb7.h"

#include "TextureNodeLink.h"

class Texture
{
public:
	static const unsigned int ASSET_NAME_SIZE = 64;

	enum class Name
	{
		STONES,
		RED_BRICK,
		DUCKWEED,
		ROCKS,
		SKYBOX_TEXTURE,
		SPACE_FRIGATE,
		WARBEAR,
		POLARBEAR,
		BUGGY,
		ASTROBOY,
		GETHWARRIOR,
		NOT_INITIALIZED
	};

public:
	Texture(const Texture &) = delete;
	Texture & operator = (const Texture &) = delete;
	~Texture() = default;

	static void Add(const char * const _assetName, const Texture::Name _name);
	static void Add(unsigned char *_assetName, const Texture::Name _name);
	static void DeleteAllTextures();
	static GLuint Find(const Texture::Name _name);

private:
	// methods
	Texture();
	static Texture *privGetInstance();

	// helper private methods
	void privLoadTexture(const char * const _assetName, GLuint *&textureID);
	void privLoadTexture(unsigned char * const _buffer, GLuint *&textureID);
	bool privLoadTGATexture(const char *szFileName, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode);
	bool privLoadTGATexture(unsigned char *_buffer, GLint minFilter, GLint magFilter, GLint horizWrapMode, GLint vertWrapMode);
	void privAddToFront(TextureNodeLink *node, TextureNodeLink *&head);
	GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);
	GLbyte *gltReadTGABits(unsigned char *_buffer, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

private:

	TextureNodeLink *active;
};

#endif