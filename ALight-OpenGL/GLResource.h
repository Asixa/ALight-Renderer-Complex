#pragma once
#include <vector>
#include "GLTexture.h"

namespace ALight_OpenGL
{
	class GLResource
	{
	public:
		static GLResource& GetInstance() { static GLResource instance; return instance; }
		std::vector<GLShader*>GLShaders;
		std::vector<GLTexture*> textures;
	};
}
