#pragma once
#include <string>
#include "stb_image.h"
namespace ALightCreator
{
	struct Texture {

	public:
		int width, height, channel;
		unsigned char* data;

		std::string type;
		std::string path;

		Texture(const char* path, const std::string& directory, bool gamma);
		void Free();
	};

	inline Texture::Texture(const char* path, const std::string& directory, bool gamma)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;
		data = stbi_load(filename.c_str(), &width, &height, &channel, 0);
	}

	inline void Texture::Free()
	{
		//free(data);
	}
}
