#pragma once
#include "../ALight-OpenGL/GLRenderer.h"

namespace ALightCreator
{
	class BufferRenderer:public Renderer
	{
	public:
		void Init() override final;
		void Update() override final;
		void Terminate() override final;
		unsigned FrameBuffer() override final;
		void Resize(int w, int h) override final;
	

		virtual void Start() {};
		virtual void Render(){};
		virtual void Destroy() {};
		unsigned char* buffer;
		int width=800, height=600;
		void InitFrameBuffer();
		bool Clear=true;
		unsigned int framebufferPointer;
		unsigned int frameColorBuffer;
	};
}
