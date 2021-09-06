#pragma once
#ifndef TEXTURE_H
 #define TEXTURE_H
 #include "glad/glad.h"

class Texture
{
public:
	unsigned int texture;
	unsigned char *data;
	int w, h, channel;
	void applyTexture(const char* path);
	void bindTexture();
};

#endif