#pragma once

#include <vector>
#include "../ALightCreator/Renderer.h"
#include "GLShader.h"
using namespace  ALightCreator;

namespace ALight_OpenGL {
	class GLRenderer :public Renderer {
	public:
		GLRenderer() {}
		void Init() override;
		void InitShader();
		void InitTexture();
		void InitData();
		void RenderLoop() override;
		void Terminate() override;
		unsigned int FrameBuffer() override;
		void Resize(int w, int h)override;
	private:
		std::vector<GLShader>GLShaders;

		
		unsigned int framebuffer;
		unsigned int textureColorbuffer;
		unsigned int rbo;
		
		int width = 800, height = 600;
		void InitFrameBuffer(int w, int h);
	};
}