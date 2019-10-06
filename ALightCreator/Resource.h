#pragma once
#include "Texture.h"
#include <vector>
#include "../ALight-OpenGL/GLShader.h"

namespace ALightCreator
{
	class  Resource
	{
	public:
		static Resource& GetInstance() { static Resource instance; return instance; }
		std::vector<Texture*> textures;
		std::vector<Shader*> shaders;

	};

}
