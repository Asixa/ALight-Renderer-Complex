#pragma once
#include <vector>
#include "Shader.h"
namespace ALightCreator {
	class  Renderer
	{
	public:
		std::vector<Shader>shaders;
		
		virtual void Init() {};
		virtual void RenderLoop() {};
		virtual void Terminate() {};
		virtual unsigned int FrameBuffer() { return 0; };
		virtual void Resize(int w, int h) {};
	};
}
