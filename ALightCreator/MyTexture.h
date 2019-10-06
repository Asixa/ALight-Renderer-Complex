// #pragma once
//
//
//
// #include <glad/glad.h>
// #include <iostream>
// #include "stb_image.h"
//
// namespace ALightCreator {
// 	class  MyTexture
// 	{
// 	public:
//
// 		unsigned int pointer;
// 		MyTexture(const char* file);
// 	};
//
// 	inline MyTexture::MyTexture(const char* file)
// 	{
// 		//static int index = 0;
// 		glGenTextures(1, &pointer);
// 		//glActiveTexture(GL_TEXTURE1 + index++);
// 		int width, height, nrComponents;
// 		unsigned char* data = stbi_load(file, &width, &height, &nrComponents, 0);
// 		if (data)
// 		{
// 			GLenum format;
// 			if (nrComponents == 1)
// 				format = GL_RED;
// 			else if (nrComponents == 3)
// 				format = GL_RGB;
// 			else if (nrComponents == 4)
// 				format = GL_RGBA;
//
// 			glBindTexture(GL_TEXTURE_2D, pointer);
// 			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
// 			glGenerateMipmap(GL_TEXTURE_2D);
//
// 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
// 			stbi_image_free(data);
// 		}
// 		else
// 		{
// 			std::cout << "Texture failed to load at path: " << file << std::endl;
// 			stbi_image_free(data);
// 		}
// 	}
// }
