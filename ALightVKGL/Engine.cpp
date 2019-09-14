#include "Engine.h"

Engine::Engine()
{
	scene = new Scene();
}

Engine& Engine::GetInstance()
{
	static Engine instance;
	return instance;
}
