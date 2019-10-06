// ALight-RayCPU.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

int a();
int main()
{
	a();
  
}
#include <iostream>
#include <thread>
#include <SDL2/SDL.h>
#include "config.h"
#include "display.h"
#include "engine.h"
#include "input.h"

using namespace math;

int a()
{
	
	// Disable cin/cout synchronization with C library buffers
	std::ios_base::sync_with_stdio(false);

	// Boolean which is used to check if the program is running or not
	bool running = true;

	// Initialize multi-threading stuff
#if THREADS>0
	const unsigned int tcount = THREADS;
#else
	const unsigned int tcount = SDL_GetCPUCount();
#endif
	std::thread* threads = new std::thread[tcount];

	// Initialize SDL2, close the program if that fails
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else
	{
		std::cout << "SDL_Init has been succesfully executed." << std::endl;
	}

	// Initialize the main display object by loading it into the stack
	Display display("ALight RayCPU", WIDTH, HEIGHT, SCALE);

	// Initialize the main camera
	Camera camera(Transform(vec3(0, 2, 0)), 2, 100);

	// Initialize the main engine object that handles the tracing
	Engine engine(&display, &camera, tcount);

	// Create SDL_Event object
	SDL_Event event;

	// Initialize rendering and updating related variables
	unsigned int frames = 0;
	unsigned int currentFrame = 0;
	unsigned int lastFrame = SDL_GetTicks();
	float deltaTime = 0;
	float frameTime = 0;

	while (running)
	{

		// Calculate delta-time & fps
		currentFrame = SDL_GetTicks();
		deltaTime = 0.1f * deltaTime + 0.9f * static_cast<float>(currentFrame - lastFrame) / 1000;
		lastFrame = currentFrame;
		frameTime = 1.0f / deltaTime;

		// Display info in console every 100th sample
		if (engine.getSamplesPPX() % 100 == 0)
			printf("dt: %.5f fps: %.5f sppx: %i\nrays cast per second: %.5f\n", deltaTime, frameTime, engine.getSamplesPPX(), WIDTH * HEIGHT * frameTime);

		// Calculate rendering of the scene
		engine.update(deltaTime);
		display.clear(0x00000000);

		for (unsigned int i = 0; i < tcount; i++)
		{
			threads[i] = std::thread([=, &engine]
				{
					engine.render(i, WIDTH, HEIGHT / tcount, 0, HEIGHT / tcount * i);
				});
		}

		for (unsigned int i = 0; i < tcount; i++)
		{
			threads[i].join();
		}

		display.render();

		// Handle input
		if (Input::g_keys[SDL_SCANCODE_W])
			camera.move(camera.getTransform().getRotation().getForwardVector(), deltaTime);
		else if (Input::g_keys[SDL_SCANCODE_S])
			camera.move(camera.getTransform().getRotation().getForwardVector(), -deltaTime);
		if (Input::g_keys[SDL_SCANCODE_A])
			camera.move(camera.getTransform().getRotation().getRightVector(), deltaTime);
		else if (Input::g_keys[SDL_SCANCODE_D])
			camera.move(camera.getTransform().getRotation().getRightVector(), -deltaTime);
		if (Input::g_keys[SDL_SCANCODE_R])
			camera.move(camera.getTransform().getRotation().getUpVector(), -deltaTime);
		else if (Input::g_keys[SDL_SCANCODE_F])
			camera.move(camera.getTransform().getRotation().getUpVector(), deltaTime);
		if (Input::g_keys[SDL_SCANCODE_UP])
			camera.rotate(camera.getTransform().getRotation().getRightVector(), deltaTime);
		else if (Input::g_keys[SDL_SCANCODE_DOWN])
			camera.rotate(camera.getTransform().getRotation().getRightVector(), -deltaTime);
		if (Input::g_keys[SDL_SCANCODE_LEFT])
			camera.rotate(camera.getTransform().getRotation().getUpVector(), deltaTime);
		else if (Input::g_keys[SDL_SCANCODE_RIGHT])
			camera.rotate(camera.getTransform().getRotation().getUpVector(), -deltaTime);
		if (Input::g_keys[SDL_SCANCODE_Q])
			camera.rotate(camera.getTransform().getRotation().getForwardVector(), -deltaTime);
		else if (Input::g_keys[SDL_SCANCODE_E])
			camera.rotate(camera.getTransform().getRotation().getForwardVector(), deltaTime);

		// Clear all samples if any key is pressed
		for (unsigned int i = 0; i < sizeof(Input::g_keys) / sizeof(*Input::g_keys); i++)
			if (Input::g_keys[i])
				engine.clearSamples();

		// Process SDL events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
			{
				auto id = event.key.keysym.scancode;
				if (id > 0 && id < sizeof(Input::g_keys) / sizeof(*Input::g_keys))
				{
					Input::g_keys[id] = true;
				}
			}
			break;
			case SDL_KEYUP:
			{
				auto id = event.key.keysym.scancode;
				if (id > 0 && id < sizeof(Input::g_keys) / sizeof(*Input::g_keys))
				{
					Input::g_keys[id] = false;
				}
			}
			break;
			}
		}

		// Increment frame counter
		frames++;
	}

	// Free allocated memory
	delete[] threads;

	// Quit SDL2 and the program after that
	SDL_Quit();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
