#pragma once
#include "../ALightCreator/BufferRenderer.h"
#include <thread>


namespace ALight_RayCPU {
	class  RayCPURenderer :public BufferRenderer
	{
		unsigned int tcount = 1;
	public:
		std::thread* threads;
		void Render() override;
		void Start() override;
		void Destroy() override;
	};
}
