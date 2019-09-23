#include "RasterRenderer.h"



void ALight_Raster::RasterRenderer::Render()
{
	for (auto i = 0; i < 800 * 600 ; i++)
	{
		auto index = i * 3;
		if (i % 10 == 0) {
			buffer[index] = 255;
			buffer[index + 1] = 0;
			buffer[index + 2] = 0;
		}
	}
}
