#pragma once
#include <string>

struct GLTexture {

public:

	int ID;
	std::string type;
	std::string path;

	GLTexture(const char* path, const std::string& directory, bool gamma);
};
