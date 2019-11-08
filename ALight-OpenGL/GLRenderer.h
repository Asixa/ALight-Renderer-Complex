#pragma once

#include <vector>
#include "../ALightCreator/Renderer.h"
using namespace  ALightCreator;

namespace ALight_OpenGL {
	class GLRenderer :public Renderer {
	public:
		GLRenderer() {}
		void Init() override;
		void InitShader();
		void InitTexture();
		void InitData();

		void Reload();
		void Update() override;
		void Terminate() override;
		unsigned int FrameBuffer() override;
		void Resize(int w, int h)override;
	private:
		

		
		unsigned int framebufferPointer;
		unsigned int frameColorBuffer;
		unsigned int frameDepthBuffer;
		
		int width = 800, height = 600;
		void InitFrameBuffer(int w, int h);
	};
}