#pragma once

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

class  Texture
{
public:
	
	unsigned int pointer;
	Texture(const char* file);
};

inline Texture::Texture(const char* file)
{
	static int index = 0;
	glGenTextures(1, &pointer);
	glActiveTexture(GL_TEXTURE1 + index++);
	int width, height, nrComponents;
	unsigned char* data = stbi_load(file, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
	
		glBindTexture(GL_TEXTURE_2D, pointer);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << file << std::endl;
		stbi_image_free(data);
	}
	
	// return ;
	// static int index=0;
	// glActiveTexture(GL_TEXTURE1+index++);
	// glGenTextures(1, &pointer);
	// glBindTexture(GL_TEXTURE_2D,pointer);
	//
	// // set the texture wrapping parameters
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// // set texture filtering parameters
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// // load image, create texture and generate mipmaps
	// int width, height, nrChannels;
	// stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// const auto data = stbi_load(file, &width, &height, &nrChannels, 0);
	// if (data)
	// {
	// 	glTexImage2D(GL_TEXTURE_2D, 0, alpha?GL_RGBA:GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	// 	glGenerateMipmap(GL_TEXTURE_2D);
	// }
	// else
	// {
	// 	std::cout << "Failed to load texture" << std::endl;
	// }
	// stbi_image_free(data);
}
