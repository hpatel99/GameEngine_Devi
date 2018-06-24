//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef CHUNK_HEADER_H
#define CHUNK_HEADER_H

enum ChunkType
{
	VERTS_TYPE = 0xA0000000,
	NORMS_TYPE,
	ANIM_TYPE,
	TEXTURE_TYPE,
	UV_TYPE,
	TGA,
	TRILIST,
};
inline const char* ToString(ChunkType v)
{
	switch (v)
	{
	case VERTS_TYPE:   return "VERTS_TYPE";
	case NORMS_TYPE:   return "NORMS_TYPE";
	case ANIM_TYPE:   return "ANIM_TYPE";
	case TEXTURE_TYPE:   return "TEXTURE_TYPE";
	case UV_TYPE:   return "UV_TYPE";
	case TGA:   return "TGA";
	case TRILIST:   return "TRILIST";
	default:      return "[Unknown OS_type]";
	}
}

struct ChunkHeader
{
	static const unsigned int CHUNK_NAME_SIZE = 20;

	// data:
	ChunkType      type;
	char           chunkName[CHUNK_NAME_SIZE];
	unsigned int   chunkSize;
	unsigned int   hashNum;
};

#endif