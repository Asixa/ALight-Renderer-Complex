#pragma once
#include <string>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"
namespace ALight_OpenGL {
	struct GLTexture {

	public:

		unsigned int ID;
		Texture* origin;

		GLTexture(Texture* t);
	};

	inline GLTexture::GLTexture(Texture* t)
	{

		static int index = 1;
		glGenTextures(1, &ID);
		glActiveTexture(GL_TEXTURE1 + index++);
		origin = t;

		if (t->data)
		{
			GLenum format;
			if (t->channel == 1)
				format = GL_RED;
			else if (t->channel == 3)
				format = GL_RGB;
			else if (t->channel == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, ID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, t->width, t->height, 0, format, GL_UNSIGNED_BYTE, t->data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << t->path << std::endl;
		}
		origin->Free();
	}
}