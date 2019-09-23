#pragma once
#include "../ALight-OpenGL/GLRenderer.h"

namespace ALightCreator
{
	class BufferRenderer:public Renderer
	{
	public:
		void Init() override;
		void Update() override;
		void Terminate() override;
		unsigned FrameBuffer() override;
		void Resize(int w, int h) override;

		virtual void Render(){};
		unsigned char* buffer;
		int width=800, height=600;
		void InitFrameBuffer();

		unsigned int framebufferPointer;
		unsigned int frameColorBuffer;
	};
}
