#pragma once
#include "../ALightCreator/Renderer.h"
using namespace  ALightCreator;
namespace ALight_Raster
{
	class  RasterRenderer:public Renderer
	{
	public:
		void Init() override;
		void RenderLoop() override;
		void Terminate() override;
		unsigned FrameBuffer() override;
		void Resize(int w, int h) override;
	};
}
