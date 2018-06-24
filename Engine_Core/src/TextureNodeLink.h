#ifndef TEXTURE_NODE_LINK_H
#define TEXTURE_NODE_LINK_H

class TextureNodeLink
{
public:
	TextureNodeLink()
	{
		this->next = 0;
		this->prev = 0;
	}

	TextureNodeLink *next;
	TextureNodeLink *prev;
};

#endif
