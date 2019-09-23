#pragma once
#include "../ALightCreator/BufferRenderer.h"
using namespace  ALightCreator;
namespace ALight_Raster
{
	class  RasterRenderer:public BufferRenderer
	{
	public:
		void Render() override;
	};
}
