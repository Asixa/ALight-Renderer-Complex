#pragma once
#include <vector>
#include "Shader.h"
namespace ALightCreator {
	class  Renderer
	{
	public:
		virtual void Init() {};
		virtual void Update() {};
		virtual void Terminate() {};
		virtual unsigned int FrameBuffer() { return 0; };
		virtual void Resize(int w, int h) {};
	};


}
