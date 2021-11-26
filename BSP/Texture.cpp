#define STB_IMAGE_IMPLEMENTATION
#include "Textures.h"
#include "stb_image.h"

void Texture::applyTexture(const char* path)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	data = stbi_load(path, &w, &h, &channel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
}
