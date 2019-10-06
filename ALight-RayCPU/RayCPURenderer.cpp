#include "RayCPURenderer.h"
#include <thread>
#include "SDL2/SDL.h"
using namespace ALight_RayCPU;
void RayCPURenderer::Render()
{
	for (unsigned int i = 0; i < tcount; i++)
	{
		// threads[i] = std::thread([=, &engine]
		// 	{
		// 		engine.render(i,width, height / tcount, 0, height / tcount * i);
		// 	});
	}

	// for (unsigned int i = 0; i < tcount; i++)
	// {
	// 	threads[i].join();
	// }
}

void RayCPURenderer::Start()
{
	tcount = SDL_GetCPUCount();
	threads = new std::thread[tcount];
}

void RayCPURenderer::Destroy()
{
}


